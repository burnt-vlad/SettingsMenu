 // SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "CustomGameUserSettings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFocalDistanseStateChanged, bool, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseSensitivityMultiplierChanged, float, Multiplier);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseXInvertationChanged, bool, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseYInvertationChanged, bool, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMasterVolumeChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicVolumeChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSFXVolumeChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIVolumeChanged, float, NewValue);

UCLASS()
class SETTINGSMENU_API UCustomGameUserSettings : public UGameUserSettings
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UCustomGameUserSettings* GetCustomGameUserSettings();

	UPROPERTY(BlueprintAssignable)
	FOnFocalDistanseStateChanged OnFocalDistanseStateChanged;
	UFUNCTION(BlueprintCallable)
	void SetUseFocalDistanse(bool State);
	UFUNCTION(BlueprintPure)
	bool GetUseFocalDistanse() const { return bUseFocalDistanse; }

	UPROPERTY(BlueprintAssignable)
	FOnMouseSensitivityMultiplierChanged OnMouseSensitivityMultiplierChanged;
	UFUNCTION(BlueprintCallable)
	void SetMouseSensitivityMultiplier(float Multiplier);
	UFUNCTION(BlueprintPure)
	float GetMouseSensitivityMultiplier() const { return MouseSensitivityMultiplier; }

	UPROPERTY(BlueprintAssignable)
	FOnMouseXInvertationChanged OnMouseXInvertationChanged;
	UFUNCTION(BlueprintCallable)
	void SetMouseXInvertation(bool State);
	UFUNCTION(BlueprintPure)
	bool GetMouseXInvertation() const { return MouseXInvertation; }

	UPROPERTY(BlueprintAssignable)
	FOnMouseYInvertationChanged OnMouseYInvertationChanged;
	UFUNCTION(BlueprintCallable)
	void SetMouseYInvertation(bool State);
	UFUNCTION(BlueprintPure)
	bool GetMouseYInvertation() const { return MouseYInvertation; }

	UFUNCTION(BlueprintCallable)
	void SetCurrentLanguageCode(FString NewLanguageCode) { CurrentLanguageCode = NewLanguageCode; }
	UFUNCTION(BlueprintPure)
	FString GetCurrentLanguageCode() const { return CurrentLanguageCode; }

	UPROPERTY(BlueprintAssignable)
	FOnMasterVolumeChanged OnMasterVolumeChanged;
	UFUNCTION(BlueprintCallable)
	void SetMasterVolume(float NewValue);
	UFUNCTION(BlueprintPure)
	float GetMasterVolume() const { return MasterVolume; }

	UPROPERTY(BlueprintAssignable)
	FOnMusicVolumeChanged OnMusicVolumeChanged;
	UFUNCTION(BlueprintCallable)
	void SetMusicVolume(float NewValue);
	UFUNCTION(BlueprintPure)
	float GetMusicVolume() const { return MusicVolume; }

	UPROPERTY(BlueprintAssignable)
	FOnSFXVolumeChanged OnSFXVolumeChanged;
	UFUNCTION(BlueprintCallable)
	void SetSFXVolume(float NewValue);
	UFUNCTION(BlueprintPure)
	float GetSFXVolume() const { return SFXVolume; }

	UPROPERTY(BlueprintAssignable)
	FOnUIVolumeChanged OnUIVolumeChanged;
	UFUNCTION(BlueprintCallable)
	void SetUIVolume(float NewValue);
	UFUNCTION(BlueprintPure)
	float GetUIVolume() const { return UIVolume; }

protected:
	//Flag indicating whether the camera will focus on nearby objects.
	UPROPERTY(Config)
	bool  bUseFocalDistanse;
	UPROPERTY(Config)
	float MouseSensitivityMultiplier;
	UPROPERTY(Config)
	bool MouseXInvertation;
	UPROPERTY(Config)
	bool MouseYInvertation;
	UPROPERTY(Config)
	FString CurrentLanguageCode;
	UPROPERTY(Config)
	float MasterVolume;
	UPROPERTY(Config)
	float MusicVolume;
	UPROPERTY(Config)
	float SFXVolume;
	UPROPERTY(Config)
	float UIVolume;
};
