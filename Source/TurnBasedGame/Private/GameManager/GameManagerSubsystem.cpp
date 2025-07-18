// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/GameManagerSubsystem.h"
#include "Unit/BaseUnit.h"
#include "PlayerPawn.h"
#include "TurnBasedGameFunctionLibrary.h"
#include "Component/UIComponent.h"
#include "TurnBasedGameMode.h"
#include "Interface/CombatInterface.h"
#include "Interface/UnitStatusInterface.h"
#include "Component/CombatComponent.h"

#include "DebugHelper.h"

void UGameManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UGameManagerSubsystem::OnPostWorldInit);
}

void UGameManagerSubsystem::ShowUnitSkillUI(const TArray<UTexture2D*> SkillCions)
{
	if (!PlayerPawn)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		PlayerPawn = Cast<APlayerPawn>(PC->GetPawn());
	}

	UTurnBasedGameFunctionLibrary::ToggleInputMode(GetWorld(), ETurnBasedGameInputMode::UIOnly);
	PlayerPawn->GetUIComponent()->OnShowSkillUI.Broadcast(SkillCions[0], SkillCions[1], SkillCions[2], SelectedUnit);
}

void UGameManagerSubsystem::ShowPlayerUnitSelect()
{
	if (!PlayerPawn)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		PlayerPawn = Cast<APlayerPawn>(PC->GetPawn());
	}

	UTurnBasedGameFunctionLibrary::ToggleInputMode(GetWorld(), ETurnBasedGameInputMode::UIOnly);
	PlayerPawn->GetUIComponent()->OnShowPlayerUnitSelectUI.Broadcast(PlayerUnitIcons);
}

void UGameManagerSubsystem::ShowEnemyUnitSelect()
{
	if (!PlayerPawn)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		PlayerPawn = Cast<APlayerPawn>(PC->GetPawn());
	}

	UTurnBasedGameFunctionLibrary::ToggleInputMode(GetWorld(), ETurnBasedGameInputMode::UIOnly);
	PlayerPawn->GetUIComponent()->OnShowEnemyUnitSelectUI.Broadcast(EnemyUnitIcons);
}

void UGameManagerSubsystem::PlayerUnitSkillActivate(ABaseUnit* PlayerUnit, int ActivateSkillNum)
{
	if (UnitSet.PlayerUnits.Contains(PlayerUnit))
	{
		if (ICombatInterface* Combet = Cast<ICombatInterface>(PlayerUnit)) { Combet->ActivateSkill(ActivateSkillNum); }
	}
	else { return; }
}

void UGameManagerSubsystem::ApplyBuffToTarget(bool IsPlayer, int index)
{
	if (IsPlayer)
	{
		if (ABaseUnit* Target = UnitSet.PlayerUnits[index])
		{
			Target->GetCombatComponent()->ActivateSkill_Buff(SavedData, Target);

			if (IsValid(SavedData.SkillMontage)) 
			{ 
				SkillUsedUnit->PlayAnimMontage(SavedData.SkillMontage); 

				if (SavedData.Buff.Type == ETurnBasedGameBuffType::Buff) { Target->PlayReactionAnim(true); }
				else { Target->PlayReactionAnim(false); }
			}
		}
	}
	else
	{
		if (ABaseUnit* Target = UnitSet.EnemyUnits[index])
		{
			Target->GetCombatComponent()->ActivateSkill_Buff(SavedData, Target);

			if (IsValid(SavedData.SkillMontage))
			{
				SkillUsedUnit->PlayAnimMontage(SavedData.SkillMontage);

				if (SavedData.Buff.Type == ETurnBasedGameBuffType::Buff) { Target->PlayReactionAnim(true); }
				else { Target->PlayReactionAnim(false); }
			}
		}
	}
}

ETurnBasedGameEffectAttribute UGameManagerSubsystem::GetBuffType() const
{
	return SavedData.Buff.Attribute;
}

void UGameManagerSubsystem::SaveSkill(ABaseUnit* SkillUnit, FSkillData Data)
{
	SkillUsedUnit = SkillUnit;
	SavedData = Data;
}

void UGameManagerSubsystem::OnPostWorldInit(UWorld* World, const UWorld::InitializationValues IVS)
{
	if (!World || !World->IsGameWorld()) { return; }

	TSubclassOf<AGameModeBase>GameModeClass = World->GetWorldSettings()->DefaultGameMode;

	if (GameModeClass->IsChildOf(ATurnBasedGameMode::StaticClass())) { UnitSet.Init(); }
	else { return; }
}

void UGameManagerSubsystem::SetSelectedUnit(ABaseUnit* Unit)
{
	if (IsValid(Unit)) { SelectedUnit = Unit; }
	else { return; }
}

ABaseUnit* UGameManagerSubsystem::GetSelectedUnit() const
{
	return SelectedUnit;
}

void UGameManagerSubsystem::Deinitialize()
{

}

void UGameManagerSubsystem::AddUnit(EUnitTeamType TeamType, ABaseUnit* Unit, UTexture2D* UnitIcon)
{
	UnitSet.AddUnit(TeamType, Unit);
	if (TeamType == EUnitTeamType::Player) { PlayerUnitIcons.Add(UnitIcon); }
	else if (TeamType == EUnitTeamType::Enemy) { EnemyUnitIcons.Add(UnitIcon); }
}

void UGameManagerSubsystem::SetCurrentTurnMode(ETurnBasedGameTurnMode NewTurnMode)
{
	CurrentTurnMode = NewTurnMode;

	ActivateTurnMode(CurrentTurnMode);
}

ETurnBasedGameTurnMode UGameManagerSubsystem::GetCurrentTurnMode() const
{
	 return CurrentTurnMode;
}

void UGameManagerSubsystem::ActivateTurnMode(ETurnBasedGameTurnMode TurnMode)
{
	switch (CurrentTurnMode)
	{
	case ETurnBasedGameTurnMode::StandbyTurn:
		Debug::Print(TEXT("StandbyTurn Activated!"), FColor::Green);

		for (ABaseUnit* Unit : UnitSet.PlayerUnits)
		{
			if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(Unit)) { Status->APRecovery(); }
			if (ICombatInterface* Combet = Cast<ICombatInterface>(Unit)) { Combet->ApplySpecificity(); }
		}

		for (ABaseUnit* Unit : UnitSet.EnemyUnits)
		{
			if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(Unit)) { Status->APRecovery(); }
			if (ICombatInterface* Combet = Cast<ICombatInterface>(Unit)) { Combet->ApplySpecificity(); }
		}
		SetCurrentTurnMode(ETurnBasedGameTurnMode::PlayerTurn);
		break;
	case ETurnBasedGameTurnMode::PlayerTurn:
		break;
	case ETurnBasedGameTurnMode::EnemyTurn:
		Debug::Print(TEXT("EnemyTurn Activated!"), FColor::Green);
		break;
	case ETurnBasedGameTurnMode::EndTurn:
		Debug::Print(TEXT("EndTurn Activated!"), FColor::Green);
		break;
	case ETurnBasedGameTurnMode::None:
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