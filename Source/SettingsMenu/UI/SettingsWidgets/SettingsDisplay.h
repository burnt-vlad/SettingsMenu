// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "SettingsDisplay.generated.h"

class USettingsSwitcher;

UCLASS()
class SETTINGSMENU_API USettingsDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	USettingsDisplay(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	void BindEvents();
	FText GetWindowModeAsText() const;
	void SetSwitcherResolutionText(FIntPoint ScreenResolution, USettingsSwitcher* Switcher);
	// Set text for key switcher based on bool
	void SetSwitcherBoolText(bool State, USettingsSwitcher* Switcher);
	void HandleLanguageSwitcher();
	void HandleWindowModeSwitcher(UCustomGameUserSettings* CustomSettings);
	void HandleResolutionSwitcher(UCustomGameUserSettings* CustomSettings);
	void HandleFrameRateSwitcher(UCustomGameUserSettings* CustomSettings);
	void HandleVSyncSwitcher(UCustomGameUserSettings* CustomSettings);
	FText ConvertLanguageCodeToDisplayText(const FString& LanguageCode);
	TArray<FIntPoint> GetSupportedResolutions(EWindowMode::Type WindowMode);

	void ChangeLanguage(int32 Delta);
	void ChangeWindowMode(int32 Delta);
	void ChangeScreenResolution(int32 Delta);
	void ChangeFrameRateLimit(int32 Delta);

	// Event handler functions
	UFUNCTION()
	void OnLanguageSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnLanguageSwitcherRightButtonClicked();
	UFUNCTION()
	void OnWindowModeSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnWindowModeSwitcherRightButtonClicked();
	UFUNCTION()
	void OnResolutionSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnResolutionSwitcherRightButtonClicked();
	UFUNCTION()
	void OnFrameRateSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnFrameRateSwitcherRightButtonClicked();
	UFUNCTION()
	void OnVSyncSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnVSyncSwitcherRightButtonClicked();
	UFUNCTION()
	void OnApplySettingsButtonClicked();

	EWindowMode::Type WindowMode;
	TArray<FIntPoint> DefaultResolutions;
	FIntPoint ScreenResolution;
	TArray<FIntPoint> SupportedResolutions;
	float FrameRateLimit;
	TArray<float> SupportedFrameRates;
	bool bEnableVSync;
	FString CurrentLanguageCode;
	TArray<FString> AvailableCultureCodes;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* LanguageSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* WindowModeSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* ResolutionSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* FrameRateSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* VSyncSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBaseButton* ApplySettingsButton;
};
