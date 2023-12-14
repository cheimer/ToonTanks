// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"


ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	check(PlayerController);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::Rotate);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);

}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::Zero();
	DeltaLocation.X = Value * MoveSpeed * GetWorld()->GetDeltaSeconds();

	AddActorLocalOffset(DeltaLocation, true);
	
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotator = FRotator::ZeroRotator;
	DeltaRotator.Add(0.0f, Value * TurnRate * GetWorld()->GetDeltaSeconds(), 0.0f);

	AddActorLocalRotation(DeltaRotator, true);

}

void ATank::Rotate(float Value)
{
	FHitResult HitInfo;
	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitInfo);

	RotateTurret(HitInfo.ImpactPoint);

}

void ATank::Fire()
{
	Super::Fire();

}
