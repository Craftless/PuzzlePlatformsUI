// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("Box Component"));
	SetRootComponent(TriggerVolume);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));
	StaticMesh -> SetupAttachment(TriggerVolume);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume -> OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnBeginOverlap);
	TriggerVolume -> OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnEndOverlap);

	for (AMovingPlatform* Platform : PlatformsToTrigger) {
		if (ensure(Platform))
			Platform -> AddActiveTrigger();
	}
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	UE_LOG(LogTemp, Warning, TEXT("Begin"));
	for (AMovingPlatform* Platform : PlatformsToTrigger) {
		if (ensure(Platform))
			Platform -> Trigger(true);
	}
}

void APlatformTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	UE_LOG(LogTemp, Warning, TEXT("End"));
	for (AMovingPlatform* Platform : PlatformsToTrigger) {
		if (ensure(Platform))
			Platform -> Trigger(false);
	}
}

