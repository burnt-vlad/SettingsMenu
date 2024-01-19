// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/PlayerControllers/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundMix.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePlayerController, All, All);

void ABasePlayerController::BeginPlay()
{
    Super::BeginPlay();
    UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
    if (CustomSettings)
    {
        SetupSoundMix(TEXT("SCM_Master"), TEXT("SC_Master"), CustomSettings, &UCustomGameUserSettings::GetMasterVolume);
        SetupSoundMix(TEXT("SCM_Music"), TEXT("SC_Music"), CustomSettings, &UCustomGameUserSettings::GetMusicVolume);
        SetupSoundMix(TEXT("SCM_SFX"), TEXT("SC_SFX"), CustomSettings, &UCustomGameUserSettings::GetSFXVolume);
        SetupSoundMix(TEXT("SCM_UI"), TEXT("SC_UI"), CustomSettings, &UCustomGameUserSettings::GetUIVolume);
    }
}

void ABasePlayerController::SetupSoundMix(const FString& SoundMixName, const FString& SoundClassName, UCustomGameUserSettings* CustomSettings, float (UCustomGameUserSettings::* VolumeFunction)() const)
{
    USoundMix* SoundMix = FindObject<USoundMix>(ANY_PACKAGE, *SoundMixName);
    USoundClass* SoundClass = FindObject<USoundClass>(ANY_PACKAGE, *SoundClassName);
    if (SoundMix && SoundClass)
    {
        UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundClass, (CustomSettings->*VolumeFunction)(), 1.0f, 0.0f, true);
    }
    else
    {
        UE_LOG(LogBasePlayerController, Error, TEXT("Failed to load %s or %s."), *SoundMixName, *SoundClassName);
    }
}
