// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/TurnBasedGameStructs.h"
#include "Types/TurnBasedGameEnums.h"
#include "CombatComponent.generated.h"

class ABaseUnit;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

	void ApplySpecificity();

	void GetAllSkillIcon(TArray<UTexture2D*>&AllSkillIcons);

	FSkillData GetSkill(int SkillNum);

	void ActivateSkill(const FSkillData& SkillData);

	FORCEINLINE bool GetSkillUsed() const { return bUsedSkill; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TArray<FBuffData> Specificity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TArray<FSkillData> Skill;

	UPROPERTY()
	ABaseUnit* OwnerUnit;

	UPROPERTY()
	bool bUsedSkill = false;

	TMultiMap<ETurnBasedGameEffectAttribute, FBuffData>BuffMap;

	void ApplyBuff(const FBuffData& Buff);
	float CalculateBufffiValue(const FBuffData& Buff);
};