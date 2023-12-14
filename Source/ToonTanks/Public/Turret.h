// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	void CheckFireCondition();

	bool IsPlayerTankInRange();

	class ATank* PlayerTank;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 800.0f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.0f;

};
