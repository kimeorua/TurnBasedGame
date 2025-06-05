// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitUIInterface.generated.h"

class UUnitUIComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TURNBASEDGAME_API IUnitUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UUnitUIComponent* GetUnitUIComponent() const = 0;
};
