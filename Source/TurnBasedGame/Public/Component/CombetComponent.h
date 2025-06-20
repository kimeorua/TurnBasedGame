// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/TurnBasedGameStructs.h"
#include "Types/TurnBasedGameEnums.h"
#include "CombetComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UCombetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombetComponent();
	TArray<FUnitSkillSet> GetSkillI() const;

	void ActivateTalent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
	TArray<FUnitSkillSet> SkillSets;

	UPROPERTY(EditDefaultsOnly, Category = "Talent", meta = (AllowPrivateAccess = "true"))
	FUnitBuffs Talents;

	TMultiMap<ETurnBasedGameEffectAttribute, FUnitBuffData> BuffMap;
};