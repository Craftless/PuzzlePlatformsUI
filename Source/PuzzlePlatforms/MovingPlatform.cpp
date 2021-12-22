// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() {
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() 
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();
    EndLocation = GetActorTransform().TransformPosition(EndLocationOffset);
    TargetLocation = EndLocation;
    BeginLocation = StartLocation;
    TargetLocations.EmplaceAt(0, BeginLocation);
    UpdateJourneyLength();

    if (HasAuthority()) {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

void AMovingPlatform::Turn() 
{
    TargetLocation = TargetLocation == EndLocation ? StartLocation : EndLocation;
    BeginLocation = BeginLocation == EndLocation ? StartLocation : EndLocation;
    UpdateJourneyLength();
}

void AMovingPlatform::Move(float DeltaTime) 
{
    float JourneyTravelled = FVector::DistSquared(GetActorLocation(), BeginLocation);
    
    if (JourneyTravelled >= JourneyLength) {
        Turn();
    }
    SetActorLocation(GetActorLocation() + (TargetLocation - GetActorLocation()).GetSafeNormal() * Speed * DeltaTime);
}

void AMovingPlatform::UpdateJourneyLength() 
{
    JourneyLength = FVector::DistSquared(TargetLocation, BeginLocation);
}

void AMovingPlatform::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    if (HasAuthority()) {
        Move(DeltaTime);
    }
}
