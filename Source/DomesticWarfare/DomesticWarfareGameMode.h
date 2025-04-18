// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ObserverCamera.h"
#include "GameFramework/GameModeBase.h"
#include "DomesticWarfareGameMode.generated.h"

UCLASS(minimalapi)
class ADomesticWarfareGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADomesticWarfareGameMode();

protected:
	TWeakObjectPtr<AObserverCamera> ObserverCamera;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};



