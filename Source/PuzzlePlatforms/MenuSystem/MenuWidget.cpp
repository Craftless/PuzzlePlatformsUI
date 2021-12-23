// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"


void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterfaceToSet) 
{
    MenuInterface = MenuInterfaceToSet;
}

void UMenuWidget::Setup() 
{
    this -> AddToViewport();
    this -> bIsFocusable = true;

    APlayerController* PlayerController = GetWorld() -> GetFirstPlayerController();
    if (!ensure(PlayerController)) return;

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this -> TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController -> SetInputMode(InputModeData);
    PlayerController -> bShowMouseCursor = true;
}

void UMenuWidget::Teardown() 
{
    RemoveFromViewport();

    bIsFocusable = false;


    APlayerController* PlayerController = GetWorld() -> GetFirstPlayerController();
    if (!ensure(PlayerController)) return;
    FInputModeGameOnly InputModeData;

    PlayerController -> SetInputMode(InputModeData);
    PlayerController -> bShowMouseCursor = false;
}
