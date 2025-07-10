// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/TurnBasedGameEnums.h"
#include "Interface/UnitStatusInterface.h"
#include "Interface/UnitUIInterface.h"
#include "Interface/CombatInterface.h"
#include "BaseUnit.generated.h"

class UUnitStatusComponent;
class UUnitUIComponent;
class UWidgetComponent;
class AUnitWeapon;

UCLASS()
class TURNBASEDGAME_API ABaseUnit : public ACharacter, public IUnitStatusInterface, public IUnitUIInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ABaseUnit();

#pragma region Mouse

	UFUNCTION()
	void UnitMouseOver(UPrimitiveComponent* TouchedComp);
	UFUNCTION()
	void UnitMouseEnd(UPrimitiveComponent* TouchedComp);
	UFUNCTION()
	void UnitClick(AActor* TouchedActor, FKey ButtonPressed);

#pragma endregion

	// ~Begin IUnitStatusInterface
	virtual UUnitStatusComponent* GetUnitStatusComponent() const override;
	// ~End IUnitStatusInterface

	// ~Begin IUnitUIInterface
	virtual UUnitUIComponent* GetUnitUIComponent() const override;
	// ~End IUnitUIInterface

	// ~Begin ICombatInterface
	virtual UCombatComponent* GetCombatComponent() const override;
	virtual void ApplySpecificity() override;
	virtual void ActivateSkill(int SkillNum) override;
	// ~End ICombatInterface

	void PlayReactionAnim(bool IsBuff);

private:

#pragma region Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitStats", meta = (AllowPrivateAccess = "true"))
	UUnitStatusComponent* UnitStatusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitStats", meta = (AllowPrivateAccess = "true"))
	UUnitUIComponent* UnitUIComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitSkill", meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;
#pragma endregion

#pragma region Status

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* UnitStatsBar;

	virtual void APRecovery() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit|Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BuffReaction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit|Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DebuffReaction = nullptr;

#pragma endregion

#pragma region Unit Weapon

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Class", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AUnitWeapon>> UnitWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Equiped", meta = (AllowPrivateAccess = "true"))
	TMap<ETurnBasedGameWeaponEquipType, AUnitWeapon*> Weapons;

	void WeaponSpawnAndAttach();

#pragma endregion

#pragma region Unit Icon
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon", meta = (AllowPrivateAccess = "true"))
	UTexture2D* UnitIcons;
#pragma endregion

protected:
	virtual void BeginPlay() override;
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	EUnitTeamType TeamType = EUnitTeamType::None;
};
