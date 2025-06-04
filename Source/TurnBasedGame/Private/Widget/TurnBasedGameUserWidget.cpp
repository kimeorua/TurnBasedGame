// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TurnBasedGameUserWidget.h"
#include "Interface/UIInterface.h"

void UTurnBasedGameUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IUIInterface* UIInterface = Cast<IUIInterface>(GetOwningPlayerPawn()))
	{
		if (UUIComponent* UIComponent = UIInterface->GetUIComponent())
		{
			BP_OnUIComponentInitalized(UIComponent);
		}
	}
}