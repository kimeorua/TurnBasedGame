// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombatComponent.h"
#include "Unit/BaseUnit.h"
#include "Component/UnitStatusComponent.h"
#include "Interface/UnitStatusInterface.h"

#include "DebugHelper.h"

UCombatComponent::UCombatComponent()
{
	OwnerUnit = nullptr;
}

void UCombatComponent::ApplyBuff(const FBuffData& Buff)
{
	if (!IsValid(OwnerUnit)) { return; }

	float Increase = 0.0f;

	switch (Buff.Attribute)
	{
	// 원복 0
	case ETurnBasedGameEffectAttribute::ATK :
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(OwnerUnit))
		{
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().ATK * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::ATK, Increase);
		}
		break;
	case ETurnBasedGameEffectAttribute::DEF:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(OwnerUnit))
		{
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().DEF * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::DEF, Increase);
		}
		break;
	case ETurnBasedGameEffectAttribute::CriticalChance:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(OwnerUnit))
		{
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().CriticalChance * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::CriticalChance, Increase);
		}
		break;
	case ETurnBasedGameEffectAttribute::Resilience:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(OwnerUnit))
		{
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().Resilience * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::Resilience, Increase);
		}
		break;
	case ETurnBasedGameEffectAttribute::Speed:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(OwnerUnit))
		{
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().Speed * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::Speed, Increase);
		}
		break;
	// 윈복 X
	case ETurnBasedGameEffectAttribute::HP:
		break;
	case ETurnBasedGameEffectAttribute::AP:
		break;
	case ETurnBasedGameEffectAttribute::Taunt:
		break;
	default:
		break;
	}
}

float UCombatComponent::CalculateBufffiValue(const FBuffData& Buff)
{
	TArray<FBuffData>BuffDataArr;
	float TempValue = 0.0f;

	if (BuffMap.Contains(Buff.Attribute))
	{
		BuffMap.MultiFind(Buff.Attribute, BuffDataArr);
		for (FBuffData Data : BuffDataArr)
		{
			if (Data.Type == ETurnBasedGameBuffType::Buff) { TempValue += Buff.Value; }
			else { TempValue -= Buff.Value; }
		}
	}
	return TempValue;
}

void UCombatComponent::ApplySpecificity()
{
	for (FBuffData Buff : Specificity)
	{
		BuffMap.Add(Buff.Attribute, Buff);
		ApplyBuff(Buff);
	}
}

void UCombatComponent::GetAllSkillIcon(TArray<UTexture2D*>& AllSkillIcons)
{
	for (FSkillData SkillData : Skill)
	{
		if (IsValid(SkillData.SkillIcon)) { AllSkillIcons.Add(SkillData.SkillIcon); }
		else { continue; }
	}
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerUnit = Cast<ABaseUnit>(GetOwner());
}