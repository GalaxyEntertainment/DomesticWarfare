// Fill out your copyright notice in the Description page of Project Settings.


#include "ObserverCamera.h"

#include "DomesticWarfare.h"
#include "DomesticWarfareCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObserverCamera::AObserverCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->bUsePawnControlRotation = false;

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

void AObserverCamera::AddUniqueViewTarget(const AController* ViewTarget)
{
	if (ViewTarget)
		ViewTargets.AddUnique(ViewTarget);
}

void AObserverCamera::RemoveUniqueViewTarget(const AController* ViewTarget)
{
	ViewTargets.RemoveSingle(ViewTarget);
}

// Called when the game starts or when spawned
void AObserverCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AObserverCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const UWorld* World = GetWorld();
	if (!World)
	{
		// This should not ever occur but just in case.
		UE_LOG(DWLog, Warning, TEXT("World not loaded at GameMode::BeginPlay()."));
		return;
	}

	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsOfClass(World, ADomesticWarfareCharacter::StaticClass(), TargetActors);
}
