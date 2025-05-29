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

    if (!IsValid(SingletonInstance))
    {
        SingletonInstance = this;
    }
}
AGameManager* AGameManager::Get(UWorld* World)
{
    if (SingletonInstance == nullptr)
    {
        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(World, AGameManager::StaticClass(), FoundActors);

        if (FoundActors.Num() > 0)
        {
            SingletonInstance = Cast<AGameManager>(FoundActors[0]);
        }
        else
        {
            SingletonInstance = nullptr;
        }
    }
    return SingletonInstance;
}

void AGameManager::UnitAdd(EUnitTeamType TeamType, ABaseUnit* AddedUnit)
{
	UnitSets.AddUnit(TeamType, AddedUnit);
}