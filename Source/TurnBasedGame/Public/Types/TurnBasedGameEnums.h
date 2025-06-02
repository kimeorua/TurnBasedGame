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
enum class ETurnBasedGAmeInputMode : uint8
{
	GameOnly,
	UIOnly
};