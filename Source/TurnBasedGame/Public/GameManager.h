// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class TURNBASEDGAME_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();
	virtual void BeginPlay() override;

	static AGameManager* Get(UWorld* World);

private:
	static AGameManager* SingletonInstance;
};
