// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UnitStatusComponent.h"

// Sets default values for this component's properties
UUnitStatusComponent::UUnitStatusComponent()
{
	
}

void UUnitStatusComponent::LevelUp()
{
	if (UnitStatus.Level < 5)
	{
		UnitStatus.Level++;
		UnitStatus.ATK += UnitStatus.LevelUpStats * UnitStatus.ATK_RiseRate;

		float Damaged = UnitStatus.MaxHP - UnitStatus.HP;

		UnitStatus.MaxHP += UnitStatus.LevelUpStats * (UnitStatus.MaxRiseRate - UnitStatus.ATK_RiseRate);
		UnitStatus.HP = UnitStatus.MaxHP - Damaged;
	}
	else { return; }
}

FUnitStatus UUnitStatusComponent::GetUnitStatus() const
{
	return UnitStatus;
}

void UUnitStatusComponent::TurnStarted()
{
	UnitStatus.AP += UnitStatus.Resilience;

	if (UnitStatus.AP >= UnitStatus.MaxAP)
	{
		UnitStatus.AP = UnitStatus.MaxAP;
	}
}

// Called when the game starts
void UUnitStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}
