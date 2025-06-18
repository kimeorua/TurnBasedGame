// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/TurnBasedGameEnums.h"
#include "Interface/UnitStatusInterface.h"
#include "Interface/UnitUIInterface.h"
#include "Interface/CombetInterface.h"
#include "BaseUnit.generated.h"

class UUnitStatusComponent;
class UUnitUIComponent;
class UWidgetComponent;
class AUnitWeapon;

UCLASS()
class TURNBASEDGAME_API ABaseUnit : public ACharacter, public IUnitStatusInterface, public IUnitUIInterface, public ICombetInterface
{
	GENERATED_BODY()

public:
	ABaseUnit();

	UFUNCTION()
	void UnitMouseOver(UPrimitiveComponent* TouchedComp);
	UFUNCTION()
	void UnitMouseEnd(UPrimitiveComponent* TouchedComp);

	UFUNCTION()
	void UnitClick(AActor* TouchedActor, FKey ButtonPressed);

	virtual UUnitStatusComponent* GetUnitStatusComponent() const override;

	virtual UUnitUIComponent* GetUnitUIComponent() const override;

	virtual UCombetComponent* GetCombetComponent() const override;

	virtual void TalentActivate() override;

	virtual void TurnStarted() const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitStats", meta = (AllowPrivateAccess = "true"))
	UUnitStatusComponent* UnitStatusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitStats", meta = (AllowPrivateAccess = "true"))
	UUnitUIComponent* UnitUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* UnitStatsBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitSkill", meta = (AllowPrivateAccess = "true"))
	UCombetComponent* CombetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Class", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AUnitWeapon>> UnitWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Equiped", meta = (AllowPrivateAccess = "true"))
	TMap<ETurnBasedGameWeaponEquipType, AUnitWeapon*> Weapons;

	void WeaponSpawnAndAttach();

protected:
	virtual void BeginPlay() override;
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	EUnitTeamType TeamType;
};
