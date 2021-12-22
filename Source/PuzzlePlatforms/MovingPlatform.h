// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 100.f;

private:
	void Turn();
	void Move(float DeltaTime);
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true)) 
	FVector EndLocationOffset = FVector(500, 0, 0);
	FVector EndLocation = FVector(0);
	FVector TargetLocation = FVector(0);
	FVector BeginLocation = FVector(0);
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	TArray<FVector> TargetLocations;
	int32 index = 1;
	FVector StartLocation = FVector(0);
	float JourneyLength;
	void UpdateJourneyLength();


	
};
