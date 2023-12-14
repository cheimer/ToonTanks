// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* PlayerController;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCameraComponent* CameraComp;

private:
	void Move(float Value);
	void Turn(float Value);
	void Rotate(float Value);

	void Fire();

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 90.0f;

};
