// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TT2025CharacterMovementComponent.generated.h"

// Перечисление для пользовательских режимов движения
UENUM(BlueprintType)
enum class ECMovementMode : uint8
{
    CMOVE_None   UMETA(DisplayName = "None"),
    CMOVE_Slide  UMETA(DisplayName = "Slide"),
    CMOVE_MAX	 UMETA(Hidden),
};

// Структура для настроек скольжения
USTRUCT(BlueprintType)
struct FSlideSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Settings")
    float MinSpeed;          // Минимальная скорость для начала скольжения

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Settings")
    float EnterImpulse;      // Импульс при входе в скольжение

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Settings")
    float Friction;          // Трение при скольжении

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Settings")
    float GravityForce;      // Гравитация при скольжении
};

UCLASS()
class TESTTASK_2025_API UTT2025CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
    bool bBlockMovementInput = false;

    // Методы для управления скольжением
    UFUNCTION(BlueprintCallable)
    void EnterSlide();
    UFUNCTION(BlueprintCallable)
    void ExitSlide();

    // Проверка, находится ли персонаж в определённом пользовательском режиме
    bool IsCustomMode(ECMovementMode Mode) const;

    // Получение поверхности под персонажем
    bool GetSurfecOnFloor(FHitResult& OutHit) const;

protected:
    UPROPERTY(BlueprintReadWrite)
    bool bWantsToSlide = false;

    // Физика скольжения
    void PhysSlide(float DeltaTime, int32 Iterations);

    // Переопределение методов родительского класса
    virtual void PhysCustom(float DeltaTime, int32 Iterations) override;
    virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
    virtual bool IsMovingOnGround() const override;

private:
    UPROPERTY(EditAnywhere, Category = "Slide Settings")
    bool bCanSlide = false;

    // Настройки скольжения
    UPROPERTY(EditAnywhere, Category = "Slide Settings")
    FSlideSettings SlideSettings;
};
