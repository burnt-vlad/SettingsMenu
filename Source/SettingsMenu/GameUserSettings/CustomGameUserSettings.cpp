// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "AudioDevice.h"

UCustomGameUserSettings::UCustomGameUserSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseFocalDistanse = true;
	MouseSensitivityMultiplier = 0.8f;
	MouseXInvertation = false;
	MouseYInvertation = false;
	CurrentLanguageCode = FString(TEXT("en"));
	FrameRateLimit = 60.f;
	MasterVolume = 1.f;
	MusicVolume = 1.f;
	SFXVolume = 1.f;
	UIVolume = 1.f;
}

UCustomGameUserSettings* UCustomGameUserSettings::GetCustomGameUserSettings()
{
	return Cast<UCustomGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}

void UCustomGameUserSettings::SetUseFocalDistanse(bool State)
{
	bUseFocalDistanse = State;
	OnFocalDistanseStateChanged.Broadcast(State);
}

void UCustomGameUserSettings::SetMouseSensitivityMultiplier(float Multiplier)
{
	MouseSensitivityMultiplier = Multiplier;
	OnMouseSensitivityMultiplierChanged.Broadcast(Multiplier);
}

void UCustomGameUserSettings::SetMouseXInvertation(bool State)
{
	MouseXInvertation = State;
	OnMouseXInvertationChanged.Broadcast(State);
}

void UCustomGameUserSettings::SetMouseYInvertation(bool State)
{
	MouseYInvertation = State;
	OnMouseYInvertationChanged.Broadcast(State);
}

void UCustomGameUserSettings::SetMasterVolume(float NewValue)
{
	MasterVolume = NewValue;
	OnMasterVolumeChanged.Broadcast(NewValue);
}

void UCustomGameUserSettings::SetMusicVolume(float NewValue)
{
	MusicVolume = NewValue;
	OnMusicVolumeChanged.Broadcast(NewValue);
}

void UCustomGameUserSettings::SetSFXVolume(float NewValue)
{
	SFXVolume = NewValue;
	OnSFXVolumeChanged.Broadcast(NewValue);
}

void UCustomGameUserSettings::SetUIVolume(float NewValue)
{
	UIVolume = NewValue;
	OnUIVolumeChanged.Broadcast(NewValue);
}
