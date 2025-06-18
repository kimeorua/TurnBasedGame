// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/TurnBasedGameEnums.h"
#include "UnitWeapon.generated.h"

class UStaticMeshComponent;

UCLASS()
class TURNBASEDGAME_API AUnitWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AUnitWeapon();

	ETurnBasedGameWeaponEquipType GetWeaponEquipType() const;
	FName GetWeaponAttachSocket() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapom|EquipType")
	ETurnBasedGameWeaponEquipType Type = ETurnBasedGameWeaponEquipType::Left;

	UPROPERTY(EditDefaultsOnly, Category = "Weapom|AttachSocket")
	FName SocketName = "";
};
