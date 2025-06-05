// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurnBasedGameUserWidget.generated.h"

class UUIComponent;
class UUnitUIComponent;

UCLASS()
class TURNBASEDGAME_API UTurnBasedGameUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On UIComponent Initalized"))
	void BP_OnUIComponentInitalized(UUIComponent* UIConponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Unit UIComponent Initalized"))
	void BP_OnUnitUIComponentInitalized(UUnitUIComponent* UnitUIComponent);

public:
	UFUNCTION(BlueprintCallable)
	void InitAndCreateUnitWidget(AActor* OwningActor);
};