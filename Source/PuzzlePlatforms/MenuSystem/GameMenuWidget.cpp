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


void UGameMenuWidget::QuitGame() 
{
    MenuInterface -> Quit();
}

void UGameMenuWidget::CancelQuit() 
{
    Teardown();
}