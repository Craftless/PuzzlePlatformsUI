// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() {
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() 
{
    Super::BeginPlay();
    InitialLocation = GetActorLocation();

    if (HasAuthority()) {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

void AMovingPlatform::Turn() 
{
    Speed = -Speed;
}

void AMovingPlatform::Move(float DeltaTime) 
{
    if ((GetActorLocation() - InitialLocation).X >= 500 || (GetActorLocation() - InitialLocation).X <= -500) {
        Turn();
    }
    SetActorLocation(GetActorLocation() + (FVector(Speed, 0, 0) * DeltaTime));
}

void AMovingPlatform::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    if (HasAuthority()) {
        Move(DeltaTime);
    }
}
