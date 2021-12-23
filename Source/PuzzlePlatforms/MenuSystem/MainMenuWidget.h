// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MenuInterface.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenuWidget : public UMenuWidget
{
	GENERATED_BODY()


public:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* Level, UWorld* World) override;


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinMenuButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinGameButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitGameButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressField = nullptr;

	UFUNCTION()
	void Host();
	UFUNCTION()
	void OpenJoinMenu();
	UFUNCTION()
	void CloseJoinMenu();
	UFUNCTION()
	void JoinGame();
	UFUNCTION()
	void ExitGame();


};
