// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/TurnBasedGameEnums.h"
#include "Types/TurnBasedGameStructs.h"
#include "GameManager.generated.h"

class ABaseUnit;
 
UCLASS()
class TURNBASEDGAME_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();
	virtual void BeginPlay() override;

	static AGameManager* Get(UWorld* World);

	void UnitAdd(EUnitTeamType TeamType, ABaseUnit* AddedUnit);

private:
	static AGameManager* SingletonInstance;

	UPROPERTY(VisibleAnywhere, Category = "Units")
	FUnitSets UnitSets;
};
