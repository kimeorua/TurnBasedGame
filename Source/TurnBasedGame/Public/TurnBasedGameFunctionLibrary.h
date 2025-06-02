// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/TurnBasedGameEnums.h"
#include "TurnBasedGameFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDGAME_API UTurnBasedGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TurnBasedGame | Function Library", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject, ETurnBasedGAmeInputMode InInputMode);

};
