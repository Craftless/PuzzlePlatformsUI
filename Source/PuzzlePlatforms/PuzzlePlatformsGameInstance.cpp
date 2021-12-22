// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"



UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer) 
{
    
}

void UPuzzlePlatformsGameInstance::Init() 
{
    
}

void UPuzzlePlatformsGameInstance::Host() 
{
    UEngine* Engine = GetEngine();
    if (!ensure(Engine)) return;
    Engine -> AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting"));

    UWorld* World = GetWorld();
    if (!ensure(World)) return;
    World -> ServerTravel("/Game/Dynamic/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address) 
{
    UEngine* Engine = GetEngine();
    if (!ensure(Engine)) return;
    Engine -> AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController)) return;
    PlayerController -> ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
