// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuWidget.h"
#include "Components/Button.h"


bool UGameMenuWidget::Initialize() 
{
    bool bSuccess = Super::Initialize();
    if (!bSuccess) return false;

    if (!ensure(QuitButton)) return false;
    if (!ensure(CancelQuitButton)) return false;

    QuitButton -> OnClicked.AddDynamic(this, &UGameMenuWidget::QuitGame);
    CancelQuitButton -> OnClicked.AddDynamic(this, &UGameMenuWidget::CancelQuit);

    return true;
}

void UGameMenuWidget::SetMenuInterface(IMenuInterface* MenuInterfaceToSet) 
{
    MenuInterface = MenuInterfaceToSet;
}

void UGameMenuWidget::QuitGame() 
{
    MenuInterface -> Quit();
}


void UGameMenuWidget::Setup() 
{
    AddToViewport();
    bIsFocusable = true;


    APlayerController* PlayerController = GetWorld() -> GetFirstPlayerController();
    if (!ensure(PlayerController)) return;
    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this -> TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController -> SetInputMode(InputModeData);
    PlayerController -> bShowMouseCursor = true;
}

void UGameMenuWidget::CancelQuit() 
{
    RemoveFromViewport();

    bIsFocusable = false;


    APlayerController* PlayerController = GetWorld() -> GetFirstPlayerController();
    if (!ensure(PlayerController)) return;
    FInputModeGameOnly InputModeData;

    PlayerController -> SetInputMode(InputModeData);
    PlayerController -> bShowMouseCursor = false;
}

