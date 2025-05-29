#include "Types/TurnBasedGameStructs.h"
#include "Unit/BaseUnit.h"

#include "DebugHelper.h"

void FUnitSets::AddUnit(EUnitTeamType TeamType, ABaseUnit* AddedUnit)
{
	if (!AddedUnit) { return; }

	Debug::Print("HI");

	switch (TeamType)
	{
	case EUnitTeamType::None:
		break;
	case EUnitTeamType::Player:
		PlayerUnits.Add(AddedUnit);
		break;
	case EUnitTeamType::Enemy:
		EnemyUnits.Add(AddedUnit);
		break;
	default:
		break;
	}
}