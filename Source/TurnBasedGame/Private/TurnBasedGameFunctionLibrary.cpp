// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedGameFunctionLibrary.h"

void UTurnBasedGameFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, ETurnBasedGAmeInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

		if (World)
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}
	if (!PlayerController) { return; }

	FInputModeGameOnly GameOnlyMode;
	FInputModeUIOnly UIOnly;

	switch (InInputMode)
	{
	case ETurnBasedGAmeInputMode::GameOnly:
		PlayerController->SetInputMode(GameOnlyMode);
		break;
	case ETurnBasedGAmeInputMode::UIOnly:
		PlayerController->SetInputMode(UIOnly);
		break;
	default:
		break;
	}
}