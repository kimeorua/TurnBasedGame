// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/BaseUnit.h"
#include "Unit/UnitAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameManager/GameManagerSubsystem.h"

#include "DebugHelper.h"

// Sets default values
ABaseUnit::ABaseUnit()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABaseUnit::UnitMouseOver(UPrimitiveComponent* TouchedComp)
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(1.0f);
}

void ABaseUnit::UnitMouseEnd(UPrimitiveComponent* TouchedComp)
{
	GetMesh()->SetRenderCustomDepth(false);
	GetMesh()->SetCustomDepthStencilValue(0.0f);
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

	AUnitAIController* AI = Cast<AUnitAIController>(GetController());

	switch (TeamType)
	{
	case EUnitTeamType::None:
		break;
	case EUnitTeamType::Player:
		AI->SetGenericTeamId(FGenericTeamId(1));
		break;
	case EUnitTeamType::Enemy:
		AI->SetGenericTeamId(FGenericTeamId(2));
		break;
	default:
		break;
	}
	
	UGameManagerSubsystem* GM = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	if (GM)
	{
		GM->AddUnit(TeamType, this);
	}

	GetCapsuleComponent()->OnBeginCursorOver.AddDynamic(this, &ABaseUnit::UnitMouseOver);
	GetCapsuleComponent()->OnEndCursorOver.AddDynamic(this, &ABaseUnit::UnitMouseEnd);
}

void ABaseUnit::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}