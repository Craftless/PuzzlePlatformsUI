// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MenuInterface.h"
#include "GameMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UGameMenuWidget : public UMenuWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelQuitButton = nullptr;

	UFUNCTION()
	void QuitGame();
	UFUNCTION()
	void CancelQuit();
	
};
