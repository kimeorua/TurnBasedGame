// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Types/TurnBasedGameEnums.h"
#include "TurnBasedGameStructs.generated.h"

class ABaseUnit;

USTRUCT(BlueprintType)
struct FUnitSets
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Units|Enemy")
	TArray<ABaseUnit*>EnemyUnits;

	UPROPERTY(VisibleAnywhere, Category = "Units|Player")
	TArray<ABaseUnit*>PlayerUnits;

	void AddUnit(EUnitTeamType TeamType, ABaseUnit* AddedUnit);
	void Init();
};
