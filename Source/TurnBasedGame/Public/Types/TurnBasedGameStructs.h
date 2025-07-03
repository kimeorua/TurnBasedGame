// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Types/TurnBasedGameEnums.h"
#include "TurnBasedGameStructs.generated.h"

class ABaseUnit;

USTRUCT(BlueprintType)
struct FUnitSets
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Units|Enemy")
	TArray<ABaseUnit*>EnemyUnits;

	UPROPERTY(VisibleAnywhere, Category = "Units|Player")
	TArray<ABaseUnit*>PlayerUnits;

	void AddUnit(EUnitTeamType TeamType, ABaseUnit* AddedUnit);
	void Init();
};

USTRUCT(BlueprintType)
struct FUnitStatus
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "UnitStatus|Type")
	EUnitType Type = EUnitType::Tanker;

	UPROPERTY(EditAnywhere, Category = "UnitStatus|Stats")
	float HP = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "UnitStatus|Stats")
	float MaxHP = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "UnitStatus|Stats")
	float AP = 2.0f;

	UPROPERTY(EditAnywhere, Category = "UnitStatus|Stats")
	float Resilience = 0.8f;

	UPROPERTY(EditAnywhere, Category = "UnitStatus|Stats")
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "UnitStatus|Stats")
	float ATK = 100.0f;

	UPROPERTY(EditAnywhere, Category = "UnitStatus|Stats")
	float DEF = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "UnitStatus|Stats")
	float ATK_RiseRate = 1.5f;

	UPROPERTY(EditAnywhere, Category = "UnitStatus|Stats", meta = (UIMin = "1", UIMax = "5"))
	int Level = 1;

	UPROPERTY(EditAnywhere, Category = "UnitStatus|Stats")
	float CriticalChance = 30.0f;

	static const int MaxLevel;

	static const float MaxRiseRate;

	static const float MaxAP;

	static const float LevelUpStats;

	float& FindStat(ETurnBasedGameEffectAttribute Attribute);
};

USTRUCT(BlueprintType)
struct FUnitSeletUISet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UnitSeletUI")
	UTexture2D* UnitIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "UnitSeletUI")
	EUnitType Type = EUnitType::Tanker;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UnitSeletUI")
	TSubclassOf<ABaseUnit>Unit;

	bool operator==(const FUnitSeletUISet& Other) const
	{
		return UnitIcon == Other.UnitIcon;
	}
};

USTRUCT(BlueprintType)
struct FEnemyUnitSpawnInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseUnit> EnemyUnitClass;

	UPROPERTY(EditAnywhere)
	TArray<FVector> SpawnLocation;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "3", UIMin = "0", UIMax = "3"))
	int32 SpawnedEnemyNum = 1;
};

USTRUCT(BlueprintType)
struct FEnemyUnitSpawnInfoTableRaw : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FEnemyUnitSpawnInfo>EnemySpawnerInfo;

	UPROPERTY(EditAnywhere)
	int32 StageNum = 1;
};

USTRUCT(BlueprintType)
struct FBuffData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	ETurnBasedGameBuffType Type = ETurnBasedGameBuffType::Buff;

	UPROPERTY(EditAnywhere)
	ETurnBasedGameEffectAttribute Attribute = ETurnBasedGameEffectAttribute::ATK;

	UPROPERTY(EditAnywhere)
	float Value = 0.0f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", ClampMax = "3", UIMin = "1", UIMax = "3"))
	int32 Turn = 1;
};

USTRUCT(BlueprintType)
struct FSkillData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	ETurnBasedGameSkillType Type = ETurnBasedGameSkillType::Attack;

	UPROPERTY(EditAnywhere)
	UAnimMontage* SkillMontage;

	UPROPERTY(EditAnywhere)
	UTexture2D* SkillIcon;

	UPROPERTY(EditAnywhere)
	ETurnBasedGameSkillTarget SkillTarget = ETurnBasedGameSkillTarget::Self;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "Type == ETurnBasedGameSkillType::Buff"))
	FBuffData Buff;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "Type == ETurnBasedGameSkillType::Attack"))
	float Rate;
};