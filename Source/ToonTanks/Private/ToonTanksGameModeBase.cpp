// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"


void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }

        GameOver(false);
    }
    else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();
        TargetTurrets--;

        if (TargetTurrets == 0)
        {
            GameOver(true);
        }
    }


}

void AToonTanksGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameModeBase::HandleGameStart()
{
    TargetTurrets = GetTargetTurretsCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
    }
}

int32 AToonTanksGameModeBase::GetTargetTurretsCount()
{
    TArray<AActor*> TurretArray;

    UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), TurretArray);

    return TurretArray.Num();


}
