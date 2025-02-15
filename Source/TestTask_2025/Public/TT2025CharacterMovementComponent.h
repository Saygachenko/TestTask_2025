// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TT2025CharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum class ECMovementMode : uint8
{
    CMOVE_None   UMETA(DisplayName = "None"),
    CMOVE_Slide  UMETA(DisplayName = "Slide"),
    CMOVE_MAX	 UMETA(Hidden),
};

USTRUCT(BlueprintType)
struct FSlideSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Settings")
    float MinSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Settings")
    float EnterImpulse;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Settings")
    float Friction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Settings")
    float GravityForce;
};

UCLASS()
class TESTTASK_2025_API UTT2025CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
    bool bBlockMovementInput = false;

    UFUNCTION(BlueprintCallable)
    void EnterSlide();
    UFUNCTION(BlueprintCallable)
    void ExitSlide();

    bool IsCustomMode(ECMovementMode Mode) const;

    bool GetSurfecOnFloor(FHitResult& OutHit) const;

protected:
    UPROPERTY(BlueprintReadWrite)
    bool bWantsToSlide = false;

    void PhysSlide(float DeltaTime, int32 Iterations);

    virtual void PhysCustom(float DeltaTime, int32 Iterations) override;
    virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
    virtual bool IsMovingOnGround() const override;

private:
    UPROPERTY(EditAnywhere, Category = "Slide Settings")
    bool bCanSlide = false;

    UPROPERTY(EditAnywhere, Category = "Slide Settings")
    FSlideSettings SlideSettings;
};
