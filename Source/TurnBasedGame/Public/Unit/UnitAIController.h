// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDGAME_API AUnitAIController : public AAIController
{
	GENERATED_BODY()
public:
	AUnitAIController(const FObjectInitializer& ObjectInitializer);
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = bEnableDetourCrowdAvoidance, UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = bEnableDetourCrowdAvoidance))
	float CollisionQueryRange = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "TeamID")
	uint8 TeamID;
};