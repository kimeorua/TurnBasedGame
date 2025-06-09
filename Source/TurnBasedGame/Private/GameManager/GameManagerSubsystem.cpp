// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GameManagerSubsystem.h"
#include "Unit/BaseUnit.h"
#include "PlayerPawn.h"
#include "TurnBasedGameFunctionLibrary.h"
#include "Component/UIComponent.h"
#include "TurnBasedGameMode.h"

#include "DebugHelper.h"

void UGameManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UGameManagerSubsystem::OnPostWorldInit);
}

void UGameManagerSubsystem::OnPostWorldInit(UWorld* World, const UWorld::InitializationValues IVS)
{
	if (!World || !World->IsGameWorld()) { return; }

	TSubclassOf<AGameModeBase>GameModeClass = World->GetWorldSettings()->DefaultGameMode;

	if (GameModeClass->IsChildOf(ATurnBasedGameMode::StaticClass()))
	{
		SetCurrentTurn(ETurnBasedGameTurnStatus::TurnBegin);
		UnitSet.Init();
	}
	else
	{
		return;
	}
}

void UGameManagerSubsystem::Deinitialize()
{

}

void UGameManagerSubsystem::AddUnit(EUnitTeamType TeamType, ABaseUnit* Unit)
{
	UnitSet.AddUnit(TeamType, Unit);

	//Debug::Print("Add Unit : " + Unit->GetActorNameOrLabel());
	//Debug::Print("Player Count : ", UnitSet.PlayerUnits.Num());
	//Debug::Print("Enemy Count : ", UnitSet.EnemyUnits.Num());
}

void UGameManagerSubsystem::ShowUnitUI(TArray<FUnitSkillSet> SkillSets)
{
	if (!PlayerPawn)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		PlayerPawn = Cast<APlayerPawn>(PC->GetPawn());
	}

	UTurnBasedGameFunctionLibrary::ToggleInputMode(GetWorld(), ETurnBasedGameInputMode::UIOnly);
	PlayerPawn->GetUIComponent()->OnShowSkillUI.Broadcast();
	PlayerPawn->GetUIComponent()->OnSkillIconSetting.Broadcast(SkillSets[0].SkillCion, SkillSets[1].SkillCion, SkillSets[2].SkillCion);
}

void UGameManagerSubsystem::SetCurrentTurn(ETurnBasedGameTurnStatus NewCurrentTurn)
{
	CurrentTurn = NewCurrentTurn;

	ActivateTurn();
}

void UGameManagerSubsystem::ActivateTurn()
{
	switch (CurrentTurn)
	{
	case ETurnBasedGameTurnStatus::TurnBegin:
		//TODO 턴 시작 (AP 회복, 특성 작동)
		Debug::Print("TurnBegin");
		break;
	case ETurnBasedGameTurnStatus::PlayerTurn:
		// TODO 플레이어 턴 (플레이어 Unit 클릭 활성 화)
		Debug::Print("PlayerTurn");
		break;
	case ETurnBasedGameTurnStatus::EnemyTurn:
		// TODO 적 턴 (적 행동 선택 개시)
		Debug::Print("EnemyTurn");
		break;
	case ETurnBasedGameTurnStatus::BattleTurn:
		// TODO 전투 (스피드 순서에 따라 행동 개시)
		Debug::Print("BattleTurn");
		break;
	case ETurnBasedGameTurnStatus::TurnEnd:
		// TODO 턴 종료 (버프 및 디버프 턴 감소
		Debug::Print("TurnEnd");
		break;
	default:
		break;
	}
}