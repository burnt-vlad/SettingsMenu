// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/Settings.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/BackgroundBlur.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/WidgetSwitcher.h"
#include "SettingsMenu/UI/SettingsWidgets/SettingsDisplay.h"
#include "SettingsMenu/UI/SettingsWidgets/SettingsGraphics.h"
#include "SettingsMenu/UI/SettingsWidgets/SettingsControls.h"
#include "SettingsMenu/UI/SettingsWidgets/SettingsAudio.h"

void USettings::NativeConstruct()
{
	Super::NativeConstruct();
	BindEvents();
}

void USettings::BindEvents()
{
	if (DisplayButton)
	{
		DisplayButton->OnButtonClicked.AddDynamic(this, &USettings::OnDisplayButtonClicked);
	}
	if (GraphicsButton)
	{
		GraphicsButton->OnButtonClicked.AddDynamic(this, &USettings::OnGraphicsButtonClicked);
	}
	if (ControlsButton)
	{
		ControlsButton->OnButtonClicked.AddDynamic(this, &USettings::OnControlsButtonClicked);
	}
	if (AudioButton)
	{
		AudioButton->OnButtonClicked.AddDynamic(this, &USettings::OnAudioButtonClicked);
	}
	if (BackButton)
	{
		BackButton->OnButtonClicked.AddDynamic(this, &USettings::OnBackButtonClicked);
	}
}

void USettings::OnDisplayButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(0);
	}
}

void USettings::OnGraphicsButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(1);
	}
}

void USettings::OnControlsButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(2);
	}
}

void USettings::OnAudioButtonClicked()
{
	if (SettingsSwitcher)
	{
		SettingsSwitcher->SetActiveWidgetIndex(3);
	}
}

void USettings::OnBackButtonClicked()
{
	OnSettingsBackButtonClickedDelegate.Broadcast();
}
