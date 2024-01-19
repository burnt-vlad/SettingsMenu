// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Elements/SettingsSwitcher.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

USettingsSwitcher::USettingsSwitcher(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    OptionTextToDisplay = FText::FromString(TEXT("Text"));
    OptionsTextToDisplay = FText::FromString(TEXT("Text"));
}

void USettingsSwitcher::NativePreConstruct()
{
    Super::NativePreConstruct();
    if (OptionTextBlock && OptionsTextBlock)
    {
        OptionTextBlock->SetText(OptionTextToDisplay);
        OptionsTextBlock->SetText(OptionsTextToDisplay);
    }
}

void USettingsSwitcher::NativeConstruct()
{
    Super::NativeConstruct();
    BindEvents();
}

void USettingsSwitcher::BindEvents()
{
    if (LeftButton)
    {
        LeftButton->OnButtonClicked.AddDynamic(this, &USettingsSwitcher::OnSwitcherLeftButtonClicked);
    }
    if (RightButton)
    {
        RightButton->OnButtonClicked.AddDynamic(this, &USettingsSwitcher::OnSwitcherRightButtonClicked);
    }
}

void USettingsSwitcher::OnSwitcherRightButtonClicked()
{
    OnRightButtonClicked.Broadcast();
}

void USettingsSwitcher::OnSwitcherLeftButtonClicked()
{
    OnLeftButtonClicked.Broadcast();
}

void USettingsSwitcher::SetOptionsTextBlock(FText TextToDisplay)
{
    OptionsTextBlock->SetText(TextToDisplay);
}
