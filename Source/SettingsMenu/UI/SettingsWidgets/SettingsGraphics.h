// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "SettingsGraphics.generated.h"

class UVerticalBox;
class USpacer;
class USettingsSwitcher;

UCLASS()
class SETTINGSMENU_API USettingsGraphics : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USettingsGraphics(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct() override;

protected:
	virtual void NativeConstruct() override;
	void BindEvents();
	bool QualityAsText(FText& OutText, int32 Index);
	void SetQualitySwitcherWidget(int32 QualityIndex, USettingsSwitcher* Switcher);
	void SetSwitcherBoolText(bool State, USettingsSwitcher* Switcher);
	void ChangeQualityIndex(int32& QualityIndex, int32 Delta, USettingsSwitcher* QualitySwitcher);
	void ChangeBoolSetting(bool& Setting, USettingsSwitcher* BoolSwitcher);

	UFUNCTION()
	void OnTextureQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnTextureQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnShadowQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnShadowQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnShadingQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnShadingQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnAntiAliasingQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnAntiAliasingQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnPostProcessQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnPostProcessQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnViewDistanceQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnViewDistanceQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnVisualEffectsQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnVisualEffectsQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnFoliageQualitySwitcherLeftButtonClicked();
	UFUNCTION()
	void OnFoliageQualitySwitcherRightButtonClicked();
	UFUNCTION()
	void OnFocalDistanceSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnFocalDistanceSwitcherRightButtonClicked();
	UFUNCTION()
	void OnApplyGraphicsSettingsButtonClicked();

	int32 TextureQualityIndex;
	int32 ShadowQualityIndex;
	int32 ShadingQualityIndex;
	int32 AntiAliasingQualityIndex;
	int32 PostProcessQualityIndex;
	int32 ViewDistanceQualityIndex;
	int32 VisualEffectsQualityIndex;
	int32 FoliageQualityIndex;
	bool bUseFocalDistance;
	TMap<int32, FText> QualityIndexToTextMap;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* TextureQualitySwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* ShadowQualitySwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* ShadingQualitySwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* AntiAliasingQualitySwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* PostProcessQualitySwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* ViewDistanceQualitySwitcher;;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* VisualEffectsQualitySwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* FoliageQualitySwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* FocalDistanceSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBaseButton* ApplySettingsButton;
};
