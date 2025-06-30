// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitStatusInterface.generated.h"

class UUnitStatusComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitStatusInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TURNBASEDGAME_API IUnitStatusInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UUnitStatusComponent* GetUnitStatusComponent() const = 0;
	virtual void APRecovery() = 0;
};
