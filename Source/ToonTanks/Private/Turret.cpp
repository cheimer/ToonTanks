// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "TimerManager.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	check(PlayerTank);

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsPlayerTankInRange())
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}

}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATurret::CheckFireCondition()
{
	if (!IsPlayerTankInRange())
		return;

	Fire();
}


bool ATurret::IsPlayerTankInRange()
{
	float Distance = FVector::Distance(GetActorLocation(), PlayerTank->GetActorLocation());

	if (Distance < FireRange)
	{
		return true;
	}

	return false;
}
