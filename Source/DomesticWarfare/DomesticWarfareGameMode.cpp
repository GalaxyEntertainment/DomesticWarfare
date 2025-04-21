// Copyright Epic Games, Inc. All Rights Reserved.

#include "DomesticWarfareGameMode.h"

#include "DomesticWarfare.h"
#include "DomesticWarfareCharacter.h"
#include "ObserverCamera.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ADomesticWarfareGameMode::ADomesticWarfareGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADomesticWarfareGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (!SetupObserverCamera())
	{
		UE_LOG(DWLog, Warning, TEXT("Observer camera setup failed."));
	}
	else
	{
		for (auto PlayerController : LoggedInPlayerControllers)
		{
			ObserverCamera->AddUniqueViewTarget(PlayerController);
		}
	}
}

void ADomesticWarfareGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	LoggedInPlayerControllers.AddUnique(NewPlayer);
}

void ADomesticWarfareGameMode::Logout(AController* Exiting)
{
	if (APlayerController* ExitingPlayerController = Cast<APlayerController>(Exiting))
	{
		LoggedInPlayerControllers.RemoveSingle(ExitingPlayerController);
	};
	
	ObserverCamera->RemoveUniqueViewTarget(Exiting);
	
	Super::Logout(Exiting);
}

bool ADomesticWarfareGameMode::SetupObserverCamera()
{
	const UWorld* World = GetWorld();
	if (!World)
	{
		// This should not ever occur but just in case.
		UE_LOG(DWLog, Warning, TEXT("World not loaded at GameMode::BeginPlay()."));
		return false; 
	}
	
	ObserverCamera = Cast<AObserverCamera>(UGameplayStatics::GetActorOfClass(World, AObserverCamera::StaticClass()));
	
	checkf(ObserverCamera.IsValid(), TEXT("Observer camera is invalid, please ensure one is placed in the world!"));
	
	if (APlayerController* PlayerController = World->GetFirstPlayerController())
	{
		PlayerController->SetViewTarget(ObserverCamera.Get());
		return true;
	}

	return false;
}
