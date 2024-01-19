// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Elements/SettingsKeySetter.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/InputKeySelector.h"

USettingsKeySetter::USettingsKeySetter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    OptionTextToDisplay = FText::FromString(TEXT("Text"));
}

void USettingsKeySetter::NativePreConstruct()
{
    Super::NativePreConstruct();
    SetDefaultOptionText();
}

void USettingsKeySetter::NativeConstruct()
{
    Super::NativeConstruct();
    BindEvents();
}

void USettingsKeySetter::BindEvents()
{
    if (KeySelector)
    {
        KeySelector->OnKeySelected.AddDynamic(this, &USettingsKeySetter::OnKeySelectedHandler);
        KeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &USettingsKeySetter::OnIsSelectedKeyChangedHandler);
    }
}

void USettingsKeySetter::SetDefaultOptionText()
{
    if (OptionTextBlock)
    {
        OptionTextBlock->SetText(OptionTextToDisplay);
    }
}

void USettingsKeySetter::OnKeySelectedHandler(FInputChord InSelectedKey)
{
    OnKeySelected.Broadcast(InSelectedKey);
}

void USettingsKeySetter::OnIsSelectedKeyChangedHandler()
{
    OnIsSelectedKeyChanged.Broadcast();
}