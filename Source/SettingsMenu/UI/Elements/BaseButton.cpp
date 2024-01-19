// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UBaseButton::UBaseButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ButtonTextToDisplay = FText::FromString(TEXT("Text"));
    InnerBorderTopPadding = 16.f;
    InnerBorderBottomPadding = -16.f;
}

void UBaseButton::NativePreConstruct()
{
    Super::NativePreConstruct();
    SetDefaultButtonText();
}

void UBaseButton::NativeConstruct()
{
    Super::NativeConstruct();
    BindEvents();
    if (InnerBorder)
    {
        InnerBorder->SetPadding(FMargin(0.f, InnerBorderTopPadding, 0.f, InnerBorderBottomPadding));
    }
}

void UBaseButton::BindEvents()
{
    if (VolumeButton)
    {
        VolumeButton->OnClicked.AddDynamic(this, &UBaseButton::OnBaseButtonClicked);
        VolumeButton->OnHovered.AddDynamic(this, &UBaseButton::OnBaseButtonHovered);
        VolumeButton->OnUnhovered.AddDynamic(this, &UBaseButton::OnBaseButtonUnhovered);
        VolumeButton->OnPressed.AddDynamic(this, &UBaseButton::OnBaseButtonPressed);
        VolumeButton->OnReleased.AddDynamic(this, &UBaseButton::OnBaseButtonReleased);
    }
}

void UBaseButton::SetDefaultButtonText()
{
    if (ButtonTextBlock)
    {
        ButtonTextBlock->SetText(ButtonTextToDisplay);
    }
}

void UBaseButton::OnBaseButtonClicked()
{
    OnButtonClicked.Broadcast();
}

void UBaseButton::OnBaseButtonHovered()
{
    OnButtonHovered.Broadcast();
}

void UBaseButton::OnBaseButtonUnhovered()
{
    OnButtonUnhovered.Broadcast();
}

void UBaseButton::OnBaseButtonPressed()
{
    OnButtonPressed.Broadcast();
}

void UBaseButton::OnBaseButtonReleased()
{
    OnButtonReleased.Broadcast();
}
