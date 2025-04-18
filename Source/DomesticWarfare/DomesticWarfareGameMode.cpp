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
	
	const UWorld* World = GetWorld();
	if (!World)
	{
		// This should not ever occur but just in case.
		UE_LOG(DWLog, Warning, TEXT("World not loaded at GameMode::BeginPlay()."));
		return; 
	}
	
	ObserverCamera = Cast<AObserverCamera>(UGameplayStatics::GetActorOfClass(World, AObserverCamera::StaticClass()));

	// Safety check since we have a weak pointer
	if (ObserverCamera.IsValid())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			PlayerController->SetViewTarget(ObserverCamera.Get());
		}
	}
}
