// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GameManagerSubsystem.h"
#include "Unit/BaseUnit.h"
#include "PlayerPawn.h"
#include "TurnBasedGameFunctionLibrary.h"
#include "Component/UIComponent.h"
#include "TurnBasedGameMode.h"
#include "Interface/CombetInterface.h"
#include "Interface/UnitStatusInterface.h"

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

		for (ABaseUnit* Unit : UnitSet.PlayerUnits)
		{
			if (ICombetInterface* CombetComponent = Cast<ICombetInterface>(Unit))
			{
				CombetComponent->TalentActivate();
			}
			if (IUnitStatusInterface* UnitStatusInterface = Cast<IUnitStatusInterface>(Unit))
			{
				UnitStatusInterface->TurnStarted();
			}
		}

		for (ABaseUnit* Unit : UnitSet.EnemyUnits)
		{
			if (ICombetInterface* CombetComponent = Cast<ICombetInterface>(Unit))
			{
				CombetComponent->TalentActivate();
			}
			if (IUnitStatusInterface* UnitStatusInterface = Cast<IUnitStatusInterface>(Unit))
			{
				UnitStatusInterface->TurnStarted();
			}
		}
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

void UGameManagerSubsystem::PickUnits()
{
	CurrentUnitUISet.Empty();

	TArray<FUnitSeletUISet> TempPool = UnitSeletUISets;

	for (int32 i = 0; i < 3 && TempPool.Num() > 0; ++i)
	{
		int32 RandIndex = FMath::RandRange(0, TempPool.Num() - 1);
		FUnitSeletUISet Picked = TempPool[RandIndex];
		CurrentUnitUISet.Add(Picked);
		TempPool.RemoveAt(RandIndex);
	}
}

void UGameManagerSubsystem::SpawnUnit(FUnitSeletUISet SpawndUnitUISet)
{
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ABaseUnit* SpawndUnit = GetWorld()->SpawnActor<ABaseUnit>(SpawndUnitUISet.Unit, Parameters);

	if (IsValid(SpawndUnit))
	{
		SpawndUnit->SetActorLocation(LocationArr[SpawnNum]);
		FRotator Rot = FRotator(0.f, 90.0f, 0.0f);
		SpawndUnit->SetActorRotation(Rot);
		SpawnNum++;

		UnitSeletUISets.Remove(SpawndUnitUISet);
		CurrentUnitUISet.Empty();
	}
	else { return; }
}

void UGameManagerSubsystem::SpawnEnemyUnit()
{
	for (const FEnemyUnitSpawnInfo& SpawnInfo : GetCurrentStageSpanwerTableRow(CurrentStage)->EnemySpawnerInfo)
	{
		if (!SpawnInfo.EnemyUnitClass) { continue; }

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		for (int i = 0; i < SpawnInfo.SpawnedEnemyNum; i++)
		{
			ABaseUnit* SpawnedEnemyUnit = GetWorld()->SpawnActor<ABaseUnit>(SpawnInfo.EnemyUnitClass, SpawnInfo.SpawnLocation[i], FRotator::ZeroRotator, SpawnParams);
			if (SpawnedEnemyUnit)
			{
				FRotator Rot = FRotator(0.0f, -90.0f, 0.0f);
				SpawnedEnemyUnit->SetActorRotation(Rot);
			}
		}
	}
}

FEnemyUnitSpawnInfoTableRaw* UGameManagerSubsystem::GetCurrentStageSpanwerTableRow(int32 StageNum) const
{
	const FName RowName = FName(TEXT("Stage") + FString::FromInt(StageNum));
	FEnemyUnitSpawnInfoTableRaw* FoundRow = EnemySpawnerDataTable->FindRow<FEnemyUnitSpawnInfoTableRaw>(RowName, FString());

	if (!FoundRow) { return nullptr; }
	return FoundRow;
}