// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/TurnBasedGameEnums.h"
#include "BaseUnit.generated.h"

UCLASS()
class TURNBASEDGAME_API ABaseUnit : public ACharacter
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

protected:
	virtual void BeginPlay() override;
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	EUnitTeamType TeamType;
};
