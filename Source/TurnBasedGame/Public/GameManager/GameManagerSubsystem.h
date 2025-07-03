#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Types/TurnBasedGameStructs.h"
#include "Types/TurnBasedGameEnums.h"
#include "GameManagerSubsystem.generated.h"

class ABaseUnit;
class APlayerPawn;

UCLASS(Blueprintable)
class TURNBASEDGAME_API UGameManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

#pragma region Init & Deinit
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
#pragma endregion

#pragma region Unit Spawn & Register

	UFUNCTION(BlueprintCallable)
	void PickUnits();

	UFUNCTION(BlueprintCallable)
	void SpawnUnit(FUnitSeletUISet SpawndUnitUISet);

	UFUNCTION(BlueprintCallable)
	void SpawnEnemyUnit();

	void AddUnit(EUnitTeamType TeamType, ABaseUnit* Unit);

#pragma endregion

#pragma region TurnMangement
	UFUNCTION(BlueprintCallable)
	void SetCurrentTurnMode(ETurnBasedGameTurnMode NewTurnMode);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ETurnBasedGameTurnMode GetCurrentTurnMode() const;

	UFUNCTION(BlueprintCallable)
	void SetSelecteType(ETurnBasedGameUnitSelecteType NewSelecteType);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ETurnBasedGameUnitSelecteType GetSelecteType() const;

	UFUNCTION(BlueprintCallable)
	void ActivateTurnMode(ETurnBasedGameTurnMode TurnMode);
#pragma endregion

#pragma region PlayerUI
	void ShowUnitSkillUI(TArray<UTexture2D*>SkillCions);
#pragma endregion

	void OnPostWorldInit(UWorld* World, const UWorld::InitializationValues IVS);
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return GetClass() != StaticClass(); }

	void SetSelectedUnit(ABaseUnit* Unit);
	ABaseUnit* GetSelectedUnit() const;

private:
#pragma region Unit
	UPROPERTY(EditAnywhere, Category = "Unit")
	FUnitSets UnitSet;
#pragma endregion

#pragma region UnitSpawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UnitSpawn|UI", meta = (AllowPrivateAccess = "true"))
	TArray<FUnitSeletUISet> UnitSeletUISets;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FUnitSeletUISet> CurrentUnitUISet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UnitSpawn|Location", meta = (AllowPrivateAccess = "true"))
	TArray<FVector>LocationArr;
#pragma endregion

#pragma region Stage
	int SpawnNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stage Clear", meta = (AllowPrivateAccess = "true"))
	int32 CurrentStage = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy Spawner Info")
	UDataTable* EnemySpawnerDataTable = nullptr;

	FEnemyUnitSpawnInfoTableRaw* GetCurrentStageSpanwerTableRow(int32 StageNum) const;
#pragma endregion

#pragma region Turn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turn", meta = (AllowPrivateAccess = "true"))
	ETurnBasedGameTurnMode CurrentTurnMode = ETurnBasedGameTurnMode::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn", meta = (AllowPrivateAccess = "true"))
	ETurnBasedGameUnitSelecteType SelecteType;
#pragma endregion

	UPROPERTY()
	APlayerPawn* PlayerPawn;

	UPROPERTY()
	ABaseUnit* SelectedUnit = nullptr;
};