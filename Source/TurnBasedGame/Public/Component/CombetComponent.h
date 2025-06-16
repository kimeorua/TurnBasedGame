// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/TurnBasedGameStructs.h"
#include "CombetComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActivateTalentDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UCombetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombetComponent();
	TArray<FUnitSkillSet> GetSkillI() const;

	UPROPERTY(BlueprintAssignable)
	FOnActivateTalentDelegate OnActivateTalent;

	void ActivateTalent() { OnActivateTalent.Broadcast(); }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
	TArray<FUnitSkillSet> SkillSets;
};