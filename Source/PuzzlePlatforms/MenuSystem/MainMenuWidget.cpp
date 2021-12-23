// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"


bool UMainMenuWidget::Initialize() 
{
    bool bSuccess = Super::Initialize();
    if (!bSuccess) return false;
    if (!ensure(HostButton)) return false;
    if (!ensure(JoinButton)) return false;
    if (!ensure(CancelJoinMenuButton)) return false;
    if (!ensure(JoinGameButton)) return false;

    HostButton -> OnClicked.AddDynamic(this, &UMainMenuWidget::Host);
    JoinButton -> OnClicked.AddDynamic(this, &UMainMenuWidget::OpenJoinMenu);
    CancelJoinMenuButton -> OnClicked.AddDynamic(this, &UMainMenuWidget::CloseJoinMenu);
    JoinGameButton -> OnClicked.AddDynamic(this, &UMainMenuWidget::JoinGame);


    return true;
}

void UMainMenuWidget::SetMenuInterface(IMenuInterface* MenuInterfaceToSet) 
{
    MenuInterface = MenuInterfaceToSet;
}

void UMainMenuWidget::Host() 
{
    if (!ensure(MenuInterface)) return;
    MenuInterface -> Host();
}

void UMainMenuWidget::OpenJoinMenu() 
{
    if (!ensure(MenuSwitcher)) return;
    if (!ensure(JoinMenu)) return;
    MenuSwitcher -> SetActiveWidget(JoinMenu);
}

void UMainMenuWidget::CloseJoinMenu() 
{
    if (!ensure(MenuSwitcher)) return;
    if (!ensure(MainMenu)) return;
    MenuSwitcher -> SetActiveWidget(MainMenu);
}

void UMainMenuWidget::JoinGame() 
{
    if (!ensure(MenuInterface)) return;
    if (!ensure(IPAddressField)) return;
    MenuInterface -> Join(IPAddressField -> GetText().ToString());
}

void UMainMenuWidget::Setup() 
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

void UMainMenuWidget::OnLevelRemovedFromWorld(ULevel* Level, UWorld* World) 
{
    Super::OnLevelRemovedFromWorld(Level, World);


    this -> RemoveFromViewport();
    this -> bIsFocusable = false;

    APlayerController* PlayerController = GetWorld() -> GetFirstPlayerController();
    if (!ensure(PlayerController)) return;

    FInputModeGameOnly InputModeData;

    PlayerController -> SetInputMode(InputModeData);
    PlayerController -> bShowMouseCursor = false;

}
