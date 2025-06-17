// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TurnBasedGameFunctionLibrary.h"
#include "Component/UIComponent.h"

APlayerPawn::APlayerPawn()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	SetRootComponent(CameraBoom);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 55.0f, 65.0f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	UIComponent = CreateDefaultSubobject<UUIComponent>(TEXT("UIComponent"));
}

UUIComponent* APlayerPawn::GetUIComponent() const
{
	return UIComponent;
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	UTurnBasedGameFunctionLibrary::ToggleInputMode(GetWorld(), ETurnBasedGameInputMode::GameOnly);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->bEnableMouseOverEvents = true;
		PlayerController->bEnableClickEvents = true;
	}
}