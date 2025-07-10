// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombatComponent.h"
#include "Unit/BaseUnit.h"
#include "Component/UnitStatusComponent.h"
#include "Interface/UnitStatusInterface.h"
#include "Interface/UnitUIInterface.h"
#include "Component/UnitUIComponent.h"

#include "DebugHelper.h"

UCombatComponent::UCombatComponent()
{
	OwnerUnit = nullptr;
}

void UCombatComponent::ApplyBuff(const FBuffData& Buff, ABaseUnit* TargetUnit)
{
	if (!IsValid(OwnerUnit)) { return; }

	float Increase = 0.0f;

	switch (Buff.Attribute)
	{
	// 원복 0
	case ETurnBasedGameEffectAttribute::ATK :
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(TargetUnit))
		{
			BuffMap.Add(Buff.Attribute, Buff);
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().ATK * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::ATK, Increase);
		}
		break;
	case ETurnBasedGameEffectAttribute::DEF:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(TargetUnit))
		{
			BuffMap.Add(Buff.Attribute, Buff);
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().DEF * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::DEF, Increase);
		}
		break;
	case ETurnBasedGameEffectAttribute::CriticalChance:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(TargetUnit))
		{
			BuffMap.Add(Buff.Attribute, Buff);
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().CriticalChance * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::CriticalChance, Increase);
		}
		break;
	case ETurnBasedGameEffectAttribute::Resilience:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(TargetUnit))
		{
			BuffMap.Add(Buff.Attribute, Buff);
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().Resilience * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::Resilience, Increase);
		}
		break;
	case ETurnBasedGameEffectAttribute::Speed:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(TargetUnit))
		{
			BuffMap.Add(Buff.Attribute, Buff);
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().Speed * CalculateBufffiValue(Buff);
			Status->GetUnitStatusComponent()->CalculateStatus(ETurnBasedGameEffectAttribute::Speed, Increase);
		}
		break;
	// 윈복 X
	case ETurnBasedGameEffectAttribute::HP:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(TargetUnit))
		{
			Increase = Status->GetUnitStatusComponent()->GetUnitStatus().MaxHP * Buff.Value;
			Status->GetUnitStatusComponent()->HealHP(Increase);

			if (IUnitUIInterface* UI = Cast<IUnitUIInterface>(TargetUnit))
			{
				UI->GetUnitUIComponent()->OnChangeHP.Broadcast(Status->GetUnitStatusComponent()->GetUnitStatus().MaxHP, Status->GetUnitStatusComponent()->GetUnitStatus().HP, Status->GetUnitStatusComponent()->GetUnitStatus().HP / Status->GetUnitStatusComponent()->GetUnitStatus().MaxHP);
			}
		}
		break;
	case ETurnBasedGameEffectAttribute::AP:
		if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(TargetUnit))
		{ 
			Status->GetUnitStatusComponent()->APUp(Buff.Value); 
			if (IUnitUIInterface* UI = Cast<IUnitUIInterface>(TargetUnit))
			{
				UI->GetUnitUIComponent()->OnChangeAP.Broadcast(Status->GetUnitStatusComponent()->GetUnitStatus().MaxAP, Status->GetUnitStatusComponent()->GetUnitStatus().AP, Status->GetUnitStatusComponent()->GetUnitStatus().AP / Status->GetUnitStatusComponent()->GetUnitStatus().MaxAP);
			}
		}
		break;
	case ETurnBasedGameEffectAttribute::Taunt:
		// 도발 구현
		break;
	default:
		break;
	}
	Debug::Print("Buff Target" + TargetUnit->GetActorNameOrLabel());
	Debug::Print("Buff Count", BuffMap.Num());
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
			if (Data.Type == ETurnBasedGameBuffType::Buff) { TempValue += Data.Value; }

			else { TempValue -= Buff.Value; }
		}
	}
	return TempValue;
}

void UCombatComponent::ApplySpecificity()
{
	for (FBuffData Buff : Specificity)
	{
		ApplyBuff(Buff, OwnerUnit);
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

FSkillData UCombatComponent::GetSkill(int SkillNum)
{
	if (SkillNum >= 0 && SkillNum < Skill.Num())
	{
		return Skill[SkillNum]; 
	}
	else { return FSkillData(); }
}

void UCombatComponent::ActivateSkill_Buff(const FSkillData& SkillData, ABaseUnit* TargetUnit)
{
	if (IUnitStatusInterface* Status = Cast<IUnitStatusInterface>(OwnerUnit))
	{
		Status->GetUnitStatusComponent()->APUp((SkillData.APCost) * -1);
		if (IUnitUIInterface* UI = Cast<IUnitUIInterface>(OwnerUnit))
		{
			UI->GetUnitUIComponent()->OnChangeAP.Broadcast(Status->GetUnitStatusComponent()->GetUnitStatus().MaxAP, Status->GetUnitStatusComponent()->GetUnitStatus().AP, Status->GetUnitStatusComponent()->GetUnitStatus().AP / Status->GetUnitStatusComponent()->GetUnitStatus().MaxAP);
		}
		ApplyBuff(SkillData.Buff, TargetUnit);

		bUsedSkill = true;
	}
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerUnit = Cast<ABaseUnit>(GetOwner());
}