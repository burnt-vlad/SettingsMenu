// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/InputSettings.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "SettingsControls.generated.h"

class USettingsSlider;
class USettingsSwitcher;
class USettingsKeySetter;

UCLASS()
class SETTINGSMENU_API USettingsControls : public UUserWidget
{
	GENERATED_BODY()

public:
	USettingsControls(const FObjectInitializer& ObjectInitializer);

protected:
	void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	void BindEvents();
	// Set default text for key setter based on existing mappings
	void SetKeySetterDefaultText(UCustomGameUserSettings* CustomSettings, USettingsKeySetter* KeySetter, FInputAxisKeyMapping& Mapping, const FName& AxisName, float Scale);
	void SetKeySetterDefaultText(UCustomGameUserSettings* CustomSettings, USettingsKeySetter* KeySetter, FInputActionKeyMapping& Mapping, const FName& ActionName);
	// Set text for key switcher based on bool
	void SetSwitcherBoolOptionsText(USettingsSwitcher* Switcher, bool Condition);
	// Get input mappings by name
	bool GetInputAxisMappingByName(FName MappingName, float Scale, FInputAxisKeyMapping& OutMapping);
	bool GetInputActionMappingByName(FName MappingName, FInputActionKeyMapping& OutMapping);
	void ChangeInputAxisMapping(const FInputAxisKeyMapping& InSelectedKey);
	void ChangeInputActionMapping(const FInputActionKeyMapping& InSelectedKey);

	// Event handler functions
	UFUNCTION()
	void OnMouseSensSliderValueChanged(float NewValue);
	UFUNCTION()
	void OnMouseXInvertSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnMouseXInvertSwitcherRightButtonClicked();
	UFUNCTION()
	void OnMouseYInvertSwitcherLeftButtonClicked();
	UFUNCTION()
	void OnMouseYInvertSwitcherRightButtonClicked();
	UFUNCTION()
	void OnMoveForwardKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnMoveBackwardKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnMoveRightKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnMoveLeftKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnJumpKeySelected(FInputChord InSelectedKey);
	UFUNCTION()
	void OnApplyControlsSettingsButtonClicked();

	// Variables to store settings
	float MouseSensitivitySliderValue;
	bool bMouseXInvertation;
	bool bMouseYInvertation;
	FInputAxisKeyMapping MoveForwardMapping;
	FInputAxisKeyMapping MoveBackwardMapping;
	FInputAxisKeyMapping MoveRightMapping;
	FInputAxisKeyMapping MoveLeftMapping;
	FInputActionKeyMapping JumpMappting;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSlider* MouseSensitivitySlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* MouseXInvertSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsSwitcher* MouseYInvertSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* MoveForwardKeySetter;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* MoveBackwardKeySetter;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* MoveRightKeySetter;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* MoveLeftKeySetter;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USettingsKeySetter* JumpKeySetter;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBaseButton* ApplySettingsButton;
};
