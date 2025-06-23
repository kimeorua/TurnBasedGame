// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitAnimInstance.h"
#include "Unit/BaseUnit.h"
#include "GameFramework/CharacterMovementComponent.h"

void UUnitAnimInstance::NativeInitializeAnimation()
{
	OwningUnit = Cast<ABaseUnit>(TryGetPawnOwner());

	if (IsValid(OwningUnit))
	{
		OwningMovementComponent = OwningUnit->GetCharacterMovement();
	}
}

void UUnitAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!IsValid(OwningUnit) || !IsValid(OwningMovementComponent)) { return; }

	GroundSpeed = OwningUnit->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.0f;
}