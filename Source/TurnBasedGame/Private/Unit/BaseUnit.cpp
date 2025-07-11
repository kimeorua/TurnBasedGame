// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/BaseUnit.h"
#include "Unit/UnitAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameManager/GameManagerSubsystem.h"
#include "Components/WidgetComponent.h"
#include "Component/UnitUIComponent.h"
#include "Component/UnitStatusComponent.h"
#include "Widget/TurnBasedGameUserWidget.h"
#include "Component/CombatComponent.h"
#include "Weapons/UnitWeapon.h"

#include "DebugHelper.h"

// Sets default values
ABaseUnit::ABaseUnit()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	UnitStatusComponent = CreateDefaultSubobject<UUnitStatusComponent>(TEXT("UnitStatusComponent"));
	UnitUIComponent = CreateDefaultSubobject<UUnitUIComponent>(TEXT("UnitUIComponent"));

	UnitStatsBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("UnitStatsBar"));
	UnitStatsBar->SetupAttachment(GetMesh());

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
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
	UGameManagerSubsystem* GM = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	if (IsValid(GM))
	{
		if (TeamType == EUnitTeamType::Player && !(GetCombatComponent()->GetSkillUsed()))
		{
			TArray<UTexture2D*>SkillIcons;
			GetCombatComponent()->GetAllSkillIcon(SkillIcons);

			GM->SetSelectedUnit(this);
			GM->ShowUnitSkillUI(SkillIcons);
			return;
		}
		else { return; }
	}
	else { return; }
}

UUnitStatusComponent* ABaseUnit::GetUnitStatusComponent() const
{
	return UnitStatusComponent;
}

void ABaseUnit::APRecovery()
{
	GetUnitStatusComponent()->APRecovery();
	UnitUIComponent->OnChangeAP.Broadcast(UnitStatusComponent->GetUnitStatus().MaxAP, UnitStatusComponent->GetUnitStatus().AP, UnitStatusComponent->GetUnitStatus().AP / UnitStatusComponent->GetUnitStatus().MaxAP);
}

void ABaseUnit::PlayReactionAnim(bool IsBuff)
{
	if (IsValid(DebuffReaction) && IsValid(BuffReaction))
	{
		if (IsBuff) { PlayAnimMontage(BuffReaction); }
		else { PlayAnimMontage(DebuffReaction); }
	}
}

UUnitUIComponent* ABaseUnit::GetUnitUIComponent() const
{
	return UnitUIComponent;
}

UCombatComponent* ABaseUnit::GetCombatComponent() const
{
	return CombatComponent;
}

void ABaseUnit::ApplySpecificity()
{
	GetCombatComponent()->ApplySpecificity();
}

void ABaseUnit::ActivateSkill(int SkillNum)
{
	FSkillData UsedSkill = GetCombatComponent()->GetSkill(SkillNum);

	UGameManagerSubsystem* GM = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();

	switch (UsedSkill.SkillTarget)
	{
	case ETurnBasedGameSkillTarget::Self:
		
		if (UsedSkill.Type == ETurnBasedGameSkillType::Attack) { return; }

		if (GetUnitStatusComponent()->GetUnitStatus().AP < UsedSkill.APCost) { return; }

		if (IsValid(UsedSkill.SkillMontage)) { PlayAnimMontage(UsedSkill.SkillMontage); }
		else { Debug::Print("AnimMontage Is Not Vaild"); }

		GetCombatComponent()->ActivateSkill_Buff(UsedSkill, this);
		break;
	case ETurnBasedGameSkillTarget::SinglePlayerUnit:

		if (UsedSkill.Type == ETurnBasedGameSkillType::Buff)
		{
			if (IsValid(GM))
			{
				GM->SaveSkill(this, UsedSkill);
				GM->ShowPlayerUnitSelect();
			}
		}
		break;
	case ETurnBasedGameSkillTarget::SingleEnemyUnit:
		if (UsedSkill.Type == ETurnBasedGameSkillType::Buff)
		{
			if (IsValid(GM))
			{
				GM->SaveSkill(this, UsedSkill);
				GM->ShowEnemyUnitSelect();
			}
		}
		break;
	case ETurnBasedGameSkillTarget::AllEnemyUnit:
		// TODO 모든 적 객체에게 적용
		break;
	case ETurnBasedGameSkillTarget::AllPlayerUnit:
		// TODO 모든 플레이어 객체 에게 적용
		break;
	default:
		break;
	}
}

void ABaseUnit::WeaponSpawnAndAttach()
{
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (TSubclassOf<AUnitWeapon> WeaponClass : UnitWeaponClass)
	{
		if (WeaponClass)
		{
			AUnitWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AUnitWeapon>(WeaponClass, Parameters);
			Weapons.Add(SpawnedWeapon->GetWeaponEquipType(), SpawnedWeapon);

			SpawnedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SpawnedWeapon->GetWeaponAttachSocket());
		}
		else { return; }
	}
}

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
		GM->AddUnit(TeamType, this, UnitIcons);
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

	WeaponSpawnAndAttach();
}

void ABaseUnit::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}