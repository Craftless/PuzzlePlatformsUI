// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenuWidget.h"
#include "MenuSystem/GameMenuWidget.h"
#include "Kismet/GameplayStatics.h"



UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer) 
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBP(TEXT("/Game/MenuSystem/Dynamic/UI/WidgetBlueprints/WBP_MainMenu"));

    if (ensure(MainMenuBP.Class)) {
        MainMenuClass = MainMenuBP.Class;
        UE_LOG(LogTemp, Warning, TEXT("[%s]"), *MainMenuClass -> GetName());
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> GameMenuBP(TEXT("/Game/MenuSystem/Dynamic/UI/WidgetBlueprints/WBP_GameMenu"));

    if (ensure(GameMenuBP.Class)) {
        GameMenuClass = GameMenuBP.Class;
        UE_LOG(LogTemp, Warning, TEXT("[%s]"), *GameMenuClass -> GetName());
    }
}

void UPuzzlePlatformsGameInstance::Init() 
{
    Super::Init();
}

void UPuzzlePlatformsGameInstance::LoadMenu() 
{
    if (!ensure(MainMenuClass)) return;
    UMainMenuWidget* Menu = CreateWidget<UMainMenuWidget>(this, MainMenuClass);
    if (!ensure(Menu)) return;
    Menu -> Setup();
    Menu -> SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadGameMenu() 
{
    if (!ensure(GameMenuClass)) return;
    UGameMenuWidget* Menu = CreateWidget<UGameMenuWidget>(this, GameMenuClass);
    if (!ensure(Menu)) return;
    Menu -> Setup();
    Menu -> SetMenuInterface(this);
}


void UPuzzlePlatformsGameInstance::Host() 
{
    UEngine* Engine = GetEngine();
    if (!ensure(Engine)) return;
    Engine -> AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting"));

    UWorld* World = GetWorld();
    if (!ensure(World)) return;
    World -> ServerTravel("/Game/PuzzlePlatforms/Dynamic/Maps/ThirdPersonExampleMap?listen");
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

void UPuzzlePlatformsGameInstance::Quit() 
{
    UEngine* Engine = GetEngine();
    if (!ensure(Engine)) return;
    Engine -> AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Quitting"));

    UGameplayStatics::OpenLevel(this, FName("MainMenu"));

}

