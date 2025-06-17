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
enum class ETurnBasedGameTurnStatus : uint8
{
	TurnBegin,
	PlayerTurn,
	EnemyTurn,
	BattleTurn,
	TurnEnd
};

UENUM(BlueprintType)
enum class ETurnBasedGameEffectAttribute : uint8
{
	HP,
	Resilience,
	Speed,
	ATK,
	DEF,
	CriticalChance,
	Taunt
};

UENUM(BlueprintType)
enum class ETurnBasedGameEffectType : uint8
{
	Buff,
	Debuff
};