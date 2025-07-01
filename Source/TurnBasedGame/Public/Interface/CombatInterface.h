// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UCombatComponent;

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TURNBASEDGAME_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual UCombatComponent* GetCombatComponent() const = 0;
};
