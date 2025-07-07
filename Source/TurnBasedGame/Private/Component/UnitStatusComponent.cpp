// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UnitStatusComponent.h"

// Sets default values for this component's properties
UUnitStatusComponent::UUnitStatusComponent()
{
	
}

void UUnitStatusComponent::APRecovery()
{
	UnitStatus.AP += UnitStatus.Resilience;
}

FUnitStatus UUnitStatusComponent::GetUnitStatus() const
{
	return UnitStatus;
}

FUnitStatus UUnitStatusComponent::GetCombetStatus() const
{
	return CombetStatus;
}

void UUnitStatusComponent::CalculateStatus(ETurnBasedGameEffectAttribute Attribute, float Value)
{
	CombetStatus.FindStat(Attribute) = UnitStatus.FindStat(Attribute) + Value;
}

void UUnitStatusComponent::HealHP(float Value)
{
	float NewHP = FMath::Clamp(UnitStatus.HP + Value, 0, UnitStatus.MaxHP);
	UnitStatus.HP = NewHP;
}

void UUnitStatusComponent::APUp(float Value)
{
	float NewAP = FMath::Clamp(UnitStatus.AP + Value, 0, UnitStatus.MaxAP);
	UnitStatus.AP = NewAP;
}

// Called when the game starts
void UUnitStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	CombetStatus = UnitStatus;
}
