// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Types/TurnBasedGameStructs.h"
#include "Types/TurnBasedGameEnums.h"
#include "GameManagerSubsystem.generated.h"

class ABaseUnit;
class APlayerPawn;

UCLASS()
class TURNBASEDGAME_API UGameManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddUnit(EUnitTeamType TeamType, ABaseUnit* Unit );

	void ShowUnitUI(TArray<FUnitSkillSet> SkillSets);

private:
	UPROPERTY(VisibleAnywhere, Category = "Unit")
	FUnitSets UnitSet;

	APlayerPawn* PlayerPawn;
};
