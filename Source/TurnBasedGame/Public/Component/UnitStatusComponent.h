// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/TurnBasedGameStructs.h"
#include "UnitStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UUnitStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnitStatusComponent();

	void APRecovery();

	FUnitStatus GetUnitStatus() const;
	FUnitStatus GetCombetStatus() const;

	void CalculateStatus(ETurnBasedGameEffectAttribute Attribute, float Value);
	void HealHP(float Value);
	void APUp(float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitStats", meta = (AllowPrivateAccess = "true"))
	FUnitStatus UnitStatus;

	UPROPERTY(VisibleAnywhere, Category = "UnitStats")
	FUnitStatus CombetStatus;
};
