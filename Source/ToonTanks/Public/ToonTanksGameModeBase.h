// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"


UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.0f;

	void HandleGameStart();


};
