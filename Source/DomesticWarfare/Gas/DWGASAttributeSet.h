// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/NinjaGASAttributeSet.h"
#include "DWGASAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class DOMESTICWARFARE_API UDWGASAttributeSet : public UNinjaGASAttributeSet
{
	GENERATED_BODY()

public: 

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UDWGASAttributeSet, Speed)

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UDWGASAttributeSet, Stamina)

	// // ------ RepNotify Functions ------ //
	// UFUNCTION()
	// virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	// UFUNCTION()
	// virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	// UFUNCTION()
	// virtual void OnRep_Speed(const FGameplayAttributeData& OldSpeed);
	// UFUNCTION()
	// virtual void OnRep_Defence(const FGameplayAttributeData& OldDefence);
	// UFUNCTION()
	// virtual void OnRep_MeleeAtkSpeed(const FGameplayAttributeData& OldMeleedAtkSpeed);
	// UFUNCTION()
	// virtual void OnRep_RangedAtkSpeed(const FGameplayAttributeData& OldRangedAtkSpeed);
	// UFUNCTION()
	// virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	// UFUNCTION()
	// virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

protected:

	// virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	// virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	// virtual void ClampAttributeChange(const FGameplayAttribute Attribute, float NewValue) const;

private:
	// virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
