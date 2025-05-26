// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedGameMode.h"
#include "GameManager.h"

#include "DebugHelper.h"

void ATurnBasedGameMode::StartPlay()
{
	Super::StartPlay();
    Debug::Print("GameMode Start");
    if (!AGameManager::Get(GetWorld()))
    {
        GetWorld()->SpawnActor<AGameManager>(AGameManager::StaticClass());
        Debug::Print("GameManager Spawn");
    }
}