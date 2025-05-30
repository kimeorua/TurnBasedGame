// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GameManagerSubsystem.h"
#include "Unit/BaseUnit.h"

#include "DebugHelper.h"

void UGameManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UnitSet.Init();
}

void UGameManagerSubsystem::Deinitialize()
{

}

void UGameManagerSubsystem::AddUnit(EUnitTeamType TeamType, ABaseUnit* Unit)
{
	UnitSet.AddUnit(TeamType, Unit);

	Debug::Print("Add Unit : " + Unit->GetActorNameOrLabel());
	Debug::Print("Player Count : ", UnitSet.PlayerUnits.Num());
	Debug::Print("Enemy Count : ", UnitSet.EnemyUnits.Num());
}
