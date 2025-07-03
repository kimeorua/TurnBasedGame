// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
enum class EUnitTeamType : uint8
{
	None,
	Player,
	Enemy
};

UENUM(BlueprintType)
enum class EUnitType : uint8
{
	Tanker UMETA(DisplayName = "Tanker"),
	Dealer UMETA(DisplayName = "Dealer"),
	Supporter UMETA(DisplayName = "Supporter")
};

UENUM(BlueprintType)
enum class ETurnBasedGameInputMode : uint8
{
	GameOnly,
	UIOnly
};

UENUM(BlueprintType)
enum class ETurnBasedGameEffectAttribute : uint8
{
	HP,
	Resilience,
	AP,
	Speed,
	ATK,
	DEF,
	CriticalChance,
	Taunt
};

UENUM(BlueprintType)
enum class ETurnBasedGameWeaponEquipType : uint8
{
	Left,
	Right
};

UENUM(BlueprintType)
enum class ETurnBasedGameTurnMode : uint8
{
	StandbyTurn UMETA(DisplayName = "StandbyTurn"),
	PlayerTurn UMETA(DisplayName = "PlayerTurn"),
	EnemyTurn UMETA(DisplayName = "EnemyTurn"),
	EndTurn UMETA(DisplayName = "EndTurn"),
	None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class ETurnBasedGameBuffType : uint8
{
	Buff UMETA(DisplayName = "Buff"),
	Debuff UMETA(DisplayName = "Debuff")
};

UENUM(BlueprintType)
enum class ETurnBasedGameSkillType : uint8
{
	Buff UMETA(DisplayName = "Buff"),
	Attack UMETA(DisplayName = "Attack")
};

UENUM(BlueprintType)
enum class ETurnBasedGameSkillTarget : uint8
{
	Self UMETA(DisplayName = "Self"),
	SinglePlayerUnit UMETA(DisplayName = "Single Player Unit"),
	SingleEnemyUnit UMETA(DisplayName = "Single Enemy Unit"),
	AllPlayerUnit UMETA(DisplayName = "All Player Unit"),
	AllEnemyUnit UMETA(DisplayName = "All Enemy Unit")
};

UENUM(BlueprintType)
enum class ETurnBasedGameUnitSelecteType : uint8
{
	TargetIsPlayerUnit,
	TargetIsEnemyUnit,
	PlayerUnit
};