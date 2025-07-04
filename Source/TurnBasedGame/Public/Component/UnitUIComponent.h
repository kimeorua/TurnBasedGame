// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnChangeHP, float, Max, float, Current, float, Persent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnChangeAP, float, Max, float, Current, float, Persent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UUnitUIComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnChangeHP OnChangeHP;

	UPROPERTY(BlueprintAssignable)
	FOnChangeAP OnChangeAP;
};
