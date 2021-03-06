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
	void Trigger(bool Move);
	void AddActiveTrigger();

private:
	void Turn();
	void Move(float DeltaTime);
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	TArray<FVector> TargetLocations;
	int32 Index = 0;
	int32 IndexMinusOne();
	FVector StartLocation = FVector(0);
	float JourneyLength;
	void UpdateJourneyLength();

	int32 NumberOfTriggers = 0;
	int32 TriggersTriggering = 0;

	
};
