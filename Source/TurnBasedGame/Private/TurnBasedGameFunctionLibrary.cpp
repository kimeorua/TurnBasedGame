// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedGameFunctionLibrary.h"

void UTurnBasedGameFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, ETurnBasedGameInputMode InInputMode)
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
	GameOnlyMode.SetConsumeCaptureMouseDown(false);

	FInputModeUIOnly UIOnly;

	switch (InInputMode)
	{
	case ETurnBasedGameInputMode::GameOnly:
		PlayerController->SetInputMode(GameOnlyMode);
		break;
	case ETurnBasedGameInputMode::UIOnly:
		PlayerController->SetInputMode(UIOnly);
		break;
	default:
		break;
	}
}