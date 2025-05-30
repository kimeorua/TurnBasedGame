#include "Types/TurnBasedGameStructs.h"
#include "Unit/BaseUnit.h"

#include "DebugHelper.h"

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