// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/BaseUnit.h"
#include "Unit/UnitAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameManager/GameManagerSubsystem.h"
#include "Components/WidgetComponent.h"
#include "Component/UnitUIComponent.h"
#include "Component/UnitStatusComponent.h"
#include "Widget/TurnBasedGameUserWidget.h"

#include "DebugHelper.h"

// Sets default values
ABaseUnit::ABaseUnit()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	UnitStatusComponent = CreateDefaultSubobject<UUnitStatusComponent>(TEXT("UnitStatusComponent"));
	UnitUIComponent = CreateDefaultSubobject<UUnitUIComponent>(TEXT("UnitUIComponent"));

	UnitStatsBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("UnitStatsBar"));
	UnitStatsBar->SetupAttachment(GetMesh());
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

void ABaseUnit::UnitClick(AActor* TouchedActor, FKey ButtonPressed)
{
	if (TeamType == EUnitTeamType::Player)
	{
		if (ButtonPressed == EKeys::LeftMouseButton)
		{
			UGameManagerSubsystem* GM = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
			if (GM)
			{
				GM->ShowUnitUI();
			}
		}
	}
	else { return; }
}

UUnitStatusComponent* ABaseUnit::GetUnitStatusComponent() const
{
	return UnitStatusComponent;
}

UUnitUIComponent* ABaseUnit::GetUnitUIComponent() const
{
	return UnitUIComponent;
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
	OnClicked.AddDynamic(this, &ABaseUnit::UnitClick);
	GetCapsuleComponent()->OnBeginCursorOver.AddDynamic(this, &ABaseUnit::UnitMouseOver);
	GetCapsuleComponent()->OnEndCursorOver.AddDynamic(this, &ABaseUnit::UnitMouseEnd);

	if (UTurnBasedGameUserWidget* StatusWidget = Cast<UTurnBasedGameUserWidget>(UnitStatsBar->GetUserWidgetObject()))
	{
		StatusWidget->InitAndCreateUnitWidget(this);

		UnitUIComponent->OnChangeHP.Broadcast(UnitStatusComponent->GetUnitStatus().MaxHP, UnitStatusComponent->GetUnitStatus().HP, UnitStatusComponent->GetUnitStatus().HP / UnitStatusComponent->GetUnitStatus().MaxHP);
		UnitUIComponent->OnChangeAP.Broadcast(UnitStatusComponent->GetUnitStatus().MaxAP, UnitStatusComponent->GetUnitStatus().AP, UnitStatusComponent->GetUnitStatus().AP / UnitStatusComponent->GetUnitStatus().MaxAP);
	}
}

void ABaseUnit::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}