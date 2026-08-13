// Fill out your copyright notice in the Description page of Project Settings.


#include "Superman.h"

// Sets default values
ASuperman::ASuperman()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASuperman::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuperman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASuperman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

