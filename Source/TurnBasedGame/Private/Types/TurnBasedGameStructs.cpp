#include "Types/TurnBasedGameStructs.h"
#include "Unit/BaseUnit.h"

void FUnitSets::AddUnit(EUnitTeamType TeamType, ABaseUnit* AddedUnit)
{
	if (!AddedUnit) { return; }

	switch (TeamType)
	{
	case EUnitTeamType::None:
		break;
	case EUnitTeamType::Player:
		PlayerUnits.AddUnique(AddedUnit);
		break;
	case EUnitTeamType::Enemy:
		EnemyUnits.AddUnique(AddedUnit);
		break;
	default:
		break;
	}
}

void FUnitSets::Init()
{
	PlayerUnits.Empty();
	EnemyUnits.Empty();
}

const float FUnitStatus::MaxRiseRate = 2.0f;
const float FUnitStatus::MaxAP = 2.0f;
const float FUnitStatus::LevelUpStats = 100.0f;
const int FUnitStatus::MaxLevel = 5;

float& FUnitStatus::FindStat(ETurnBasedGameEffectAttribute Attribute)
{
	switch (Attribute)
	{
	case ETurnBasedGameEffectAttribute::HP:
		return HP;
	case ETurnBasedGameEffectAttribute::Resilience:
		return Resilience;
	case ETurnBasedGameEffectAttribute::AP:
		return AP;
	case ETurnBasedGameEffectAttribute::Speed:
		return Speed;
	case ETurnBasedGameEffectAttribute::ATK:
		return ATK;
	case ETurnBasedGameEffectAttribute::DEF:
		return DEF;
	case ETurnBasedGameEffectAttribute::CriticalChance:
		return CriticalChance;
	default:
		checkNoEntry(); // 디버깅 시 충돌
		static float DummyStat = 0.0f;
		return DummyStat;
	}
}
