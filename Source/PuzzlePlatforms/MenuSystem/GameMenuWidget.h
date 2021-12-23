// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "GameMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	void SetMenuInterface(IMenuInterface* MenuInterfaceToSet);
	void Setup();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelQuitButton = nullptr;

	UFUNCTION()
	void QuitGame();
	UFUNCTION()
	void CancelQuit();

	IMenuInterface* MenuInterface = nullptr;
	
};
