// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "DebugHelper.h"

AGameManager* AGameManager::SingletonInstance = nullptr;

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (!SingletonInstance)
	{
		SingletonInstance = this;

		Debug::Print("GameManager Create");
	}

	Debug::Print("GameManager Start");
}
AGameManager* AGameManager::Get(UWorld* World)
{
	return SingletonInstance;
}
