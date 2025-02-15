// Fill out your copyright notice in the Description page of Project Settings.


#include "TT2025CharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

bool UTT2025CharacterMovementComponent::IsCustomMode(ECMovementMode Mode) const
{

	return MovementMode == MOVE_Custom && CustomMovementMode == static_cast<uint8>(Mode);
}

void UTT2025CharacterMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
	switch (CustomMovementMode)
	{
	case static_cast<uint8>(ECMovementMode::CMOVE_Slide):

		PhysSlide(DeltaTime, Iterations);
		break;

	default:

		break;
	}
}

void UTT2025CharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	if (MovementMode == MOVE_Walking && bCanSlide && bWantsToSlide)
	{
		FHitResult HitResut;
		if (GetSurfecOnFloor(HitResut) && Velocity.Length() > SlideSettings.MinSpeed)
		{
			EnterSlide();
		}
	}

	if (IsCustomMode(ECMovementMode::CMOVE_Slide) && !bCanSlide)
	{
		ExitSlide();
	}

	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
}

bool UTT2025CharacterMovementComponent::IsMovingOnGround() const
{
	return Super::IsMovingOnGround() || IsCustomMode(ECMovementMode::CMOVE_Slide);
}

void UTT2025CharacterMovementComponent::EnterSlide()
{
	bBlockMovementInput = true;
	bWantsToSlide = true;

	Velocity += Velocity.GetSafeNormal2D() * SlideSettings.EnterImpulse;

	SetMovementMode(EMovementMode::MOVE_Custom, static_cast<uint8>(ECMovementMode::CMOVE_Slide));
}

void UTT2025CharacterMovementComponent::PhysSlide(float DeltaTime, int32 Iterations)
{
	if (DeltaTime < MIN_TICK_TIME)
	{
		return;
	}

	RestorePreAdditiveRootMotionVelocity();

	FHitResult HitResult;

	if (!GetSurfecOnFloor(HitResult) || Velocity.Size2D() < SlideSettings.MinSpeed)
	{
		ExitSlide();
		StartNewPhysics(DeltaTime, Iterations);

		return;
	}

	if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		CalcVelocity(DeltaTime, SlideSettings.Friction, true, GetMaxBrakingDeceleration());
	}

	Velocity += SlideSettings.GravityForce * FVector::DownVector * DeltaTime;

	Iterations++;
	bJustTeleported = false;

	FVector OldLocation = UpdatedComponent->GetComponentLocation();
	const FVector DeltaVelocity = Velocity * DeltaTime;
	const FVector PlaneDirection = FVector::VectorPlaneProject(UpdatedComponent->GetForwardVector(), HitResult.Normal).GetSafeNormal();
	FQuat NewRotation = FRotationMatrix::MakeFromXZ(PlaneDirection, HitResult.Normal).ToQuat();
	HitResult = FHitResult(1.f);
	SafeMoveUpdatedComponent(DeltaVelocity, NewRotation, true, HitResult);

	if (HitResult.bBlockingHit)
	{
		ExitSlide();
	}

	if (!bJustTeleported && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / DeltaTime;
	}
}

void UTT2025CharacterMovementComponent::ExitSlide()
{
	bWantsToSlide = false;
	bBlockMovementInput = false;

	FQuat NewRotation = FRotationMatrix::MakeFromXZ(UpdatedComponent->GetForwardVector().GetSafeNormal2D(), FVector::UpVector).ToQuat();
	FHitResult HitResult;
	SafeMoveUpdatedComponent(FVector::ZeroVector, NewRotation, true, HitResult);

	SetMovementMode(EMovementMode::MOVE_Walking);
}

bool UTT2025CharacterMovementComponent::GetSurfecOnFloor(FHitResult& OutHit) const
{
	const FVector Start = UpdatedComponent->GetComponentLocation();
	const FVector End = Start + CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.f * FVector::DownVector;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(CharacterOwner);

	return GetWorld()->LineTraceSingleByProfile(OutHit, Start, End, TEXT("BlockAll"), CollisionQueryParams);
}