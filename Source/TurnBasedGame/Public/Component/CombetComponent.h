// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/TurnBasedGameStructs.h"
#include "Types/TurnBasedGameEnums.h"
#include "CombetComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UCombetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombetComponent();

protected:
	virtual void BeginPlay() override;

private:
};