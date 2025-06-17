// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombetComponent.h"

#include "DebugHelper.h"

UCombetComponent::UCombetComponent()
{

}

TArray<FUnitSkillSet> UCombetComponent::GetSkillI() const
{
	return SkillSets;
}

void UCombetComponent::ActivateTalent()
{
	for (FUnitBuffData BuffData : Talents.BuffData)
	{
		BuffMap.Add(BuffData.Attribute, BuffData);
	}
	Debug::Print( GetOwner()->GetActorNameOrLabel() + " Buff Count : ", BuffMap.Num());
}

void UCombetComponent::BeginPlay()
{
	Super::BeginPlay();
}