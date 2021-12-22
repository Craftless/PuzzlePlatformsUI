// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "DrawDebugHelpers.h"


AMovingPlatform::AMovingPlatform() {
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() 
{
    Super::BeginPlay();

    TargetLocations.Insert(FVector(0), 0);
    // for (FVector Location : TargetLocations) {
    //     Location += GetActorLocation();
    // }
    for (int32 i = 0; i < TargetLocations.Num(); i++)
    {
        TargetLocations[i] += GetActorLocation();
    }
    
    UpdateJourneyLength();

    if (HasAuthority()) {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

void AMovingPlatform::Turn() 
{
    if (Index + 1 > TargetLocations.Num() - 1) {
        Index = 0;
    }
    else {
        Index++;
    }
    UpdateJourneyLength();
}

void AMovingPlatform::Move(float DeltaTime) 
{
    if (TriggersTriggering <= 0 && NumberOfTriggers > 0) return;
    if (TargetLocations.Num() <= 1) return;
    float JourneyTravelled = FVector::DistSquared(GetActorLocation(), TargetLocations[IndexMinusOne()]);
    
    if (JourneyTravelled >= JourneyLength) {
        Turn();
    }
    SetActorLocation(GetActorLocation() + (TargetLocations[Index] - GetActorLocation()).GetSafeNormal() * Speed * DeltaTime);
}

int32 AMovingPlatform::IndexMinusOne() 
{
    return Index - 1 < 0 ? TargetLocations.Num() - 1 : Index - 1;
}

void AMovingPlatform::UpdateJourneyLength() 
{
    JourneyLength = FVector::DistSquared(TargetLocations[IndexMinusOne()], TargetLocations[Index]);
}

void AMovingPlatform::Trigger(bool Move) 
{
    if (Move) TriggersTriggering++;
    else if (TriggersTriggering > 0) TriggersTriggering--;
}

void AMovingPlatform::AddActiveTrigger() 
{
    NumberOfTriggers++;
}

void AMovingPlatform::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    if (HasAuthority()) {
        Move(DeltaTime);
    }
}
