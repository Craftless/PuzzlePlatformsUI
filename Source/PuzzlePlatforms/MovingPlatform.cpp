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

    StartLocation = GetActorLocation();
    EndLocation = GetActorTransform().TransformPosition(EndLocationOffset);
    TargetLocation = EndLocation;
    BeginLocation = StartLocation;
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

    for (FVector Location : TargetLocations) {
        DrawDebugSphere(GetWorld(), Location, 50.f, 16, FColor::Red, false, 0.f, 0.f, 50.f);
    }

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

void AMovingPlatform::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    if (HasAuthority()) {
        Move(DeltaTime);
    }
}
