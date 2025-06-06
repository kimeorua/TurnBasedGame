// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombetComponent.h"

UCombetComponent::UCombetComponent()
{

}

TArray<FUnitSkillSet> UCombetComponent::GetSkillI() const
{
	return SkillSets;
}

void UCombetComponent::BeginPlay()
{
	Super::BeginPlay();
}