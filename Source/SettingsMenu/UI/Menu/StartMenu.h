// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitButtonClicked);

UCLASS()
class SETTINGSMENU_API UStartMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// BlueprintAssignable delegates for button click events
	UPROPERTY(BlueprintAssignable)
	FOnPlayButtonClicked OnPlayButtonClickedDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnSettingsButtonClicked OnSettingsButtonClickedDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnExitButtonClicked OnExitButtonClickedDelegate;

protected:
	virtual void NativeConstruct() override;
	void BindEvents();

	// Event handler functions for button clicks
	UFUNCTION()
	void OnPlayButtonClicked();
	UFUNCTION()
	void OnSettingsButtonClicked();
	UFUNCTION()
	void OnExitButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UBaseButton* PlayButton;
	UPROPERTY(meta = (BindWidget))
	class UBaseButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	class UBaseButton* ExitButton;
};
