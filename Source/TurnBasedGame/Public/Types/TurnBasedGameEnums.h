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
	Human,
	Mechanic,
	Wild
};

UENUM(BlueprintType)
enum class ETurnBasedGameInputMode : uint8
{
	GameOnly,
	UIOnly
};