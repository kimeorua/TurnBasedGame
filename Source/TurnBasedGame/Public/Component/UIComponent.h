// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShowSkillUI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSkillIconSetting, UTexture2D*, Icon1, UTexture2D*, Icon2, UTexture2D*, Icon3);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable)
	FOnShowSkillUI OnShowSkillUI;

	UPROPERTY(BlueprintAssignable)
	FOnSkillIconSetting OnSkillIconSetting;
};