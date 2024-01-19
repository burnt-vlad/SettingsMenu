// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Elements/SettingsSlider.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/Slider.h"

USettingsSlider::USettingsSlider(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    OptionTextToDisplay = FText::FromString(TEXT("Text"));
    SliderMinValue = 0.0f;
    SliderMaxValue = 1.f;
    SliderStepSizeValue = 0.01f;
}

void USettingsSlider::NativePreConstruct()
{
    Super::NativePreConstruct();
    SetDefaultOptionText();
}

void USettingsSlider::NativeConstruct()
{
    Super::NativeConstruct();
    BindEvents();
    if (OptionSlider)
    {
        OptionSlider->SetMinValue(SliderMinValue);
        OptionSlider->SetMaxValue(SliderMaxValue);
        OptionSlider->SetStepSize(SliderStepSizeValue);
        if (SliderMaterial)
        {
            SetupSliderStyle();
        }
    }
}

void USettingsSlider::BindEvents()
{
    if (OptionSlider)
    {
        OptionSlider->OnValueChanged.AddDynamic(this, &USettingsSlider::OnSettingsSliderValueChanged);
    }
}

void USettingsSlider::SetDefaultOptionText()
{
    if (OptionTextBlock)
    {
        OptionTextBlock->SetText(OptionTextToDisplay);
    }
}

void USettingsSlider::SetupSliderStyle()
{
    DynamicMaterial = UMaterialInstanceDynamic::Create(SliderMaterial, this, FName(TEXT("Value")));

    if (DynamicMaterial)
    {
        FSlateBrush BarSlateBrush;
        BarSlateBrush.SetImageSize(FVector2D(256.f, 256.f));
        BarSlateBrush.DrawAs = ESlateBrushDrawType::Image;
        BarSlateBrush.Tiling = ESlateBrushTileType::NoTile;
        BarSlateBrush.Mirroring = ESlateBrushMirrorType::NoMirror;
        BarSlateBrush.SetResourceObject(DynamicMaterial);

        FSlateBrush ThumblateBrush;
        ThumblateBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
        ThumblateBrush.Tiling = ESlateBrushTileType::NoTile;
        ThumblateBrush.Mirroring = ESlateBrushMirrorType::NoMirror;

        FSliderStyle SliderStyle;
        SliderStyle.NormalBarImage = BarSlateBrush;
        SliderStyle.HoveredBarImage = BarSlateBrush;
        SliderStyle.DisabledBarImage = BarSlateBrush;
        SliderStyle.NormalThumbImage = ThumblateBrush;
        SliderStyle.HoveredThumbImage = ThumblateBrush;
        SliderStyle.DisabledThumbImage = ThumblateBrush;
        SliderStyle.BarThickness = 75.f;

        OptionSlider->WidgetStyle = SliderStyle;
    }
}

void USettingsSlider::OnSettingsSliderValueChanged(float NewValue)
{
    OnSliderValueChanged.Broadcast(NewValue);
    float ClampedValue = FMath::Clamp(NewValue, SliderMinValue, SliderMaxValue);
    SetSliderValueInternal(ClampedValue);
}

void USettingsSlider::SetSliderValue(float NewValue)
{
    float ClampedValue = FMath::Clamp(NewValue, SliderMinValue, SliderMaxValue);
    SetSliderValueInternal(ClampedValue);
}

void USettingsSlider::SetSliderValueInternal(float NewValue)
{
    OptionSlider->SetValue(NewValue);
    if (DynamicMaterial)
    {
        DynamicMaterial->SetScalarParameterValue(FName(TEXT("Value")), NewValue);
    }
}
