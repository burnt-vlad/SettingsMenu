// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsSlider.generated.h"

class UHorizontalBox;
class UBorder;
class UTextBlock;
class USlider;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderValueChanged, float, NewValue);

UCLASS()
class SETTINGSMENU_API USettingsSlider : public UUserWidget
{
	GENERATED_BODY()

public:
    USettingsSlider(const FObjectInitializer& ObjectInitializer);
    void SetSliderValue(float NewValue);

    // BlueprintAssignable delegates for key-related events
    UPROPERTY(BlueprintAssignable)
    FOnSliderValueChanged OnSliderValueChanged;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText OptionTextToDisplay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
    float SliderMinValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
    float SliderMaxValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
    float SliderStepSizeValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
    UMaterialInterface* SliderMaterial;
    UMaterialInstanceDynamic* DynamicMaterial;

protected:
    virtual void NativeConstruct() override;
    void NativePreConstruct() override;
    void SetupSliderStyle();
    void BindEvents();
    void SetDefaultOptionText();
    void SetSliderValueInternal(float NewValue);

    // Event handler functions
    UFUNCTION()
    void OnSettingsSliderValueChanged(float NewValue);

    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionTextBlock;
    UPROPERTY(meta = (BindWidget))
    USlider* OptionSlider;
};
