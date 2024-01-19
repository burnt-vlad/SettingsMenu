// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Settings.generated.h"

class UBaseButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsBackButtonClicked);

UCLASS()
class SETTINGSMENU_API USettings : public UUserWidget
{
	GENERATED_BODY()

public:
	// BlueprintAssignable delegates for button click events
	UPROPERTY(BlueprintAssignable)
	FOnSettingsBackButtonClicked OnSettingsBackButtonClickedDelegate;

protected:
	virtual void NativeConstruct() override;
	void BindEvents();
	UFUNCTION(BlueprintCallable)
	UBaseButton* GetBackButton() const { return BackButton; }

	// Event handler functions for button clicks
	UFUNCTION()
	void OnDisplayButtonClicked();
	UFUNCTION()
	void OnGraphicsButtonClicked();
	UFUNCTION()
	void OnControlsButtonClicked();
	UFUNCTION()
	void OnAudioButtonClicked();
	UFUNCTION()
	void OnBackButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UBaseButton* DisplayButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* GraphicsButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* ControlsButton;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* AudioButton;
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* SettingsSwitcher;
	UPROPERTY(meta = (BindWidget))
	class USettingsDisplay* DisplaySettings;
	UPROPERTY(meta = (BindWidget))
	class USettingsGraphics* GraphicsSettings;
	UPROPERTY(meta = (BindWidget))
	class USettingsControls* ControlsSettings;
	UPROPERTY(meta = (BindWidget))
	class USettingsAudio* AudioSettings;
	UPROPERTY(meta = (BindWidget))
	UBaseButton* BackButton;
};
