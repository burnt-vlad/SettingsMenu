// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnContinueButtonClicked_IGM);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestartButtonClicked_IGM);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsButtonClicked_IGM);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMainMenuButtonClicked_IGM);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitButtonClicked_IGM);

UCLASS()
class SETTINGSMENU_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// BlueprintAssignable delegates for button click events
	UPROPERTY(BlueprintAssignable)
	FOnContinueButtonClicked_IGM OnContinueButtonClickedDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnRestartButtonClicked_IGM OnRestartButtonClickedDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnSettingsButtonClicked_IGM OnSettingsButtonClickedDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnMainMenuButtonClicked_IGM OnMainMenuButtonClickedDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnExitButtonClicked_IGM OnExitButtonClickedDelegate;

protected:
	virtual void NativeConstruct() override;
	void BindEvents();

	// Event handler functions for button clicks
	UFUNCTION()
	void OnContinueButtonClicked();
	UFUNCTION()
	void OnRestartButtonClicked();
	UFUNCTION()
	void OnSettingsButtonClicked();
	UFUNCTION()
	void OnMainMenuButtonClicked();
	UFUNCTION()
	void OnExitButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UBaseButton* ContinueButton;
	UPROPERTY(meta = (BindWidget))
	class UBaseButton* RestartButton;
	UPROPERTY(meta = (BindWidget))
	class UBaseButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	class UBaseButton* MainMenuButton;
	UPROPERTY(meta = (BindWidget))
	class UBaseButton* ExitButton;
};
