// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombetInterface.generated.h"

class UCombetComponent;

UINTERFACE(MinimalAPI)
class UCombetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TURNBASEDGAME_API ICombetInterface
{
	GENERATED_BODY()

public:
	virtual UCombetComponent* GetCombetComponent() const = 0;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TalentActivate();
};
