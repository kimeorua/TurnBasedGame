// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIComponent.generated.h"

class UTexture2D;
class ABaseUnit;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnShowSkillUI, UTexture2D*, SkillIcon1, UTexture2D*, SkillIcon2, UTexture2D*, SkillIcon3, ABaseUnit*, SkillUsingUnit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowPlayerUnitSelectUI, const TArray<UTexture2D*>&, Icons);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowEnemyUnitSelectUI, const TArray<UTexture2D*>&, Icons);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnShowSkillUI OnShowSkillUI;

	UPROPERTY(BlueprintAssignable)
	FOnShowPlayerUnitSelectUI OnShowPlayerUnitSelectUI;

	UPROPERTY(BlueprintAssignable)
	FOnShowEnemyUnitSelectUI OnShowEnemyUnitSelectUI;
};