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

// Called when the game starts
void UUnitStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}
