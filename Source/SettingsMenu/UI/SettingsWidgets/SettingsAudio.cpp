// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/SettingsAudio.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "SettingsMenu/UI/Elements/SettingsSlider.h"
#include "Components/Spacer.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"

DEFINE_LOG_CATEGORY_STATIC(LogSettingsAudio, All, All);

void USettingsAudio::NativeConstruct()
{
	Super::NativeConstruct();
	BindEvents();
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomSettings)
	{
		SetSlidersDefaultValue(CustomSettings);
	}
}

void USettingsAudio::BindEvents()
{
	if (MasterVolumeSlider)
	{
		MasterVolumeSlider->OnSliderValueChanged.AddDynamic(this, &USettingsAudio::OnMasterVolumeValueChanged);
	}
	if (MusicVolumeSlider)
	{
		MusicVolumeSlider->OnSliderValueChanged.AddDynamic(this, &USettingsAudio::OnMusicVolumeValueChanged);
	}
	if (SFXVolumeSlider)
	{
		SFXVolumeSlider->OnSliderValueChanged.AddDynamic(this, &USettingsAudio::OnSFXVolumeValueChanged);
	}
	if (UIVolumeSlider)
	{
		UIVolumeSlider->OnSliderValueChanged.AddDynamic(this, &USettingsAudio::OnUIVolumeValueChanged);
	}
}

void USettingsAudio::SetVolumeSliderDefaultValue(float& VolumeValue, USettingsSlider* VolumeSlider, float (UCustomGameUserSettings::* GetVolumeFunction)() const, UCustomGameUserSettings* Settings)
{
	if (Settings)
	{
		float SettingsVolume = (Settings->*GetVolumeFunction)();
		VolumeValue = SettingsVolume;
		VolumeSlider->SetSliderValue(SettingsVolume);
	}
}

void USettingsAudio::SetSlidersDefaultValue(UCustomGameUserSettings* Settings)
{
	SetVolumeSliderDefaultValue(MasterVolumeValue, MasterVolumeSlider, &UCustomGameUserSettings::GetMasterVolume, Settings);
	SetVolumeSliderDefaultValue(MusicVolumeValue, MusicVolumeSlider, &UCustomGameUserSettings::GetMusicVolume, Settings);
	SetVolumeSliderDefaultValue(SFXVolumeValue, SFXVolumeSlider, &UCustomGameUserSettings::GetSFXVolume, Settings);
	SetVolumeSliderDefaultValue(UIVolumeValue, UIVolumeSlider, &UCustomGameUserSettings::GetUIVolume, Settings);
}

void USettingsAudio::OnMasterVolumeValueChanged(float NewValue)
{
	MasterVolumeValue = NewValue;
}

void USettingsAudio::OnMusicVolumeValueChanged(float NewValue)
{
	MusicVolumeValue = NewValue;
}

void USettingsAudio::OnSFXVolumeValueChanged(float NewValue)
{
	SFXVolumeValue = NewValue;
}

void USettingsAudio::OnUIVolumeValueChanged(float NewValue)
{
	UIVolumeValue = NewValue;
}



