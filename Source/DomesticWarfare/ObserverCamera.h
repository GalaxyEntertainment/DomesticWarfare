// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObserverCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;


UCLASS()
class DOMESTICWARFARE_API AObserverCamera : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraComponent, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraComponent, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
	
public:	
	AObserverCamera();

	TObjectPtr<const UCameraComponent> GetCameraComponent() const { return Camera; }
	void AddUniqueViewTarget(const AController* ViewTarget);
	void RemoveUniqueViewTarget(const AController* ViewTarget);

protected:
	UPROPERTY()
	TArray<TObjectPtr<const AController>> ViewTargets;

	// Zoom Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	bool EnableZoomAdjustments = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float ZoomFactor = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MinZoom = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MaxZoom = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float ZoomInterpSpeed = 3.0f;
	//
	
	virtual void BeginPlay() override;
	
	virtual FVector CalcBoundingBoxAroundViewTargets();
	
	/**
	 * Calculates how much to zoom in and out to allow all targets to be in view without breaking the min and max limits.
	 *  
	 * If using a perspective camera, zooming is often best handled via FOV rather than distance, especially if there's 
	 * a risk of objects getting clipped or distorted due to perspective.
	 */
	virtual void AdjustCameraZoomToFitTargets(FVector ViewTargetsExtent, float DeltaTime);

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void AdjustCameraSettings(float DeltaTime);

};
