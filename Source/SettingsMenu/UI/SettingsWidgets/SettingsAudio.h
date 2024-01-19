// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "SettingsAudio.generated.h"

class USettingsSlider;

UCLASS()
class SETTINGSMENU_API USettingsAudio : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	void BindEvents();
	// Setting default value for a specific slider
	void SetVolumeSliderDefaultValue(float& VolumeValue, USettingsSlider* VolumeSlider, float (UCustomGameUserSettings::* GetVolumeFunction)() const, UCustomGameUserSettings* Settings);
	// Setting default values for all sliders in the widget
	void SetSlidersDefaultValue(UCustomGameUserSettings* Settings);

	// Event handler functions for slider changes
	UFUNCTION()
	void OnMasterVolumeValueChanged(float NewValue);
	UFUNCTION()
	void OnMusicVolumeValueChanged(float NewValue);
	UFUNCTION()
	void OnSFXVolumeValueChanged(float NewValue);
	UFUNCTION()
	void OnUIVolumeValueChanged(float NewValue);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Audio Settings")
	float MasterVolumeValue;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Audio Settings")
	float MusicVolumeValue;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Audio Settings")
	float SFXVolumeValue;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Audio Settings")
	float UIVolumeValue;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* MasterVolumeSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* MusicVolumeSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* SFXVolumeSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* UIVolumeSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBaseButton* ApplySettingsButton;
};
