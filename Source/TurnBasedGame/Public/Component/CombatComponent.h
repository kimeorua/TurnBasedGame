// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/TurnBasedGameStructs.h"
#include "Types/TurnBasedGameEnums.h"
#include "CombatComponent.generated.h"

class ABaseUnit;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

	void ApplySpecificity();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	FBuffData Specificity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	FSkillData Skill;

	UPROPERTY()
	ABaseUnit* OwnerUnit;

	TMultiMap<ETurnBasedGameEffectAttribute, FBuffData>BuffMap;

	void ApplyBuff(const FBuffData& Buff);
	float CalculateBufffiValue(const FBuffData& Buff);
};