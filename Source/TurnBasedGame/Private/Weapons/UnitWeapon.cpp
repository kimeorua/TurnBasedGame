// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/UnitWeapon.h"
#include "Components/StaticMeshComponent.h"

AUnitWeapon::AUnitWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

ETurnBasedGameWeaponEquipType AUnitWeapon::GetWeaponEquipType() const
{
	return Type;
}

FName AUnitWeapon::GetWeaponAttachSocket() const
{
	return SocketName;
}

void AUnitWeapon::BeginPlay()
{
	Super::BeginPlay();
}