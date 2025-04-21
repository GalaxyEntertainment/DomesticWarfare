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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
	
public:	
	AObserverCamera();

	TObjectPtr<const UCameraComponent> GetCameraComponent() const { return Camera; }
	void AddUniqueViewTarget(const AController* ViewTarget);
	void RemoveUniqueViewTarget(const AController* ViewTarget);

protected:
	UPROPERTY()
	TArray<TObjectPtr<const AController>> ViewTargets;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
