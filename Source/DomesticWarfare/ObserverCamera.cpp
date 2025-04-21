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

	// !) Temp code for testing
	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADomesticWarfareCharacter::StaticClass(), Characters);
	
	for (AActor* Character : Characters)
	{
		ViewTargets.AddUnique(Character->GetInstigatorController());
	}
}

FVector AObserverCamera::CalcBoundingBoxAroundViewTargets()
{
	// The below calculation can be done using GetActorArrayBounds(ViewTargets, false, Center, Extent) 
	// from UGameplayStatics but would require removing the ViewTargets Const and converting to raw ptr.
	FBox ActorBoundingBox(EForceInit::ForceInit);
	
	for (auto ViewTarget : ViewTargets)
	{
		if (IsValid(ViewTarget))
		{
			ActorBoundingBox += ViewTarget->GetCharacter()->GetActorLocation();
		}
	}
	
	if (ActorBoundingBox.IsValid)
	{
		FVector Center = ActorBoundingBox.GetCenter();
		FVector Extent = ActorBoundingBox.GetExtent(); // Half-size

		// Move the camera to focus on center
        SetActorLocation(Center);

		return Extent;
	}

	return FVector::ZeroVector;
}

void AObserverCamera::AdjustCameraZoomToFitTargets(FVector ViewTargetsExtent, float DeltaTime)
{
	if (ViewTargetsExtent == FVector::ZeroVector)
	{
		UE_LOG(DWLog, Warning, TEXT("Failed to calculate the bounds encompassing the view targets."));
		return;
	}

	// Adjust spring arm len
	float DesiredArmLength = ViewTargetsExtent.Size() * ZoomFactor; 
	CameraSpringArm->TargetArmLength = FMath::Clamp(DesiredArmLength, MinZoom, MaxZoom);
	
	// Smooth Adjustments
	float SmoothedLength = FMath::FInterpTo(CameraSpringArm->TargetArmLength, DesiredArmLength, DeltaTime, ZoomInterpSpeed);
	CameraSpringArm->TargetArmLength = SmoothedLength;
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

	AdjustCameraSettings(DeltaTime);
}


void AObserverCamera::AdjustCameraSettings(float DeltaTime)
{
	FVector Extent = CalcBoundingBoxAroundViewTargets();

	if (EnableZoomAdjustments)
		AdjustCameraZoomToFitTargets(Extent, DeltaTime);
}