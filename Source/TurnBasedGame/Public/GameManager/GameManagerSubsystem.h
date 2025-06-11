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
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddUnit(EUnitTeamType TeamType, ABaseUnit* Unit );

	void ShowUnitUI(TArray<FUnitSkillSet> SkillSets);

	void OnPostWorldInit(UWorld* World, const UWorld::InitializationValues IVS);

	UFUNCTION(BlueprintCallable)
	void SetCurrentTurn(ETurnBasedGameTurnStatus NewCurrentTurn);

	void ActivateTurn();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return GetClass() != StaticClass(); }

	UFUNCTION(BlueprintCallable)
	void PickUnits();

	UFUNCTION(BlueprintCallable)
	void SpawnUnit(FUnitSeletUISet SpawndUnitUISet);

private:
	UPROPERTY(VisibleAnywhere, Category = "Unit")
	FUnitSets UnitSet;

	UPROPERTY()
	APlayerPawn* PlayerPawn;

	UPROPERTY()
	ETurnBasedGameTurnStatus CurrentTurn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Unit Icons", meta = (AllowPrivateAccess = "true"))
	TArray<FUnitSeletUISet> UnitSeletUISets;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FUnitSeletUISet> CurrentUnitUISet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Unit Spawn Location", meta = (AllowPrivateAccess = "true"))
	TArray<FVector>LocationArr;

	int SpawnNum = 0;
};