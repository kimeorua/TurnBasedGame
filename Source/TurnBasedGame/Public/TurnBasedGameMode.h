// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TurnBasedGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDGAME_API ATurnBasedGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;
};
