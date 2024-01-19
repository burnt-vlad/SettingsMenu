// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/SettingsGraphics.h"
#include "SettingsMenu/UI/Elements/SettingsSwitcher.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Components/Spacer.h"

DEFINE_LOG_CATEGORY_STATIC(LogSettingsGraphics, All, All);

USettingsGraphics::USettingsGraphics(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	QualityIndexToTextMap = 
	{
	{0, FText::FromString(TEXT("Low"))},
	{ 1, FText::FromString(TEXT("Medium")) },
	{ 2, FText::FromString(TEXT("High")) },
	{ 3, FText::FromString(TEXT("Ultra")) },
	{ 4, FText::FromString(TEXT("Epic"))} 
	};
}

void USettingsGraphics::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USettingsGraphics::NativeConstruct()
{
	Super::NativeConstruct();
	BindEvents();
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomSettings)
	{
		if (TextureQualitySwitcher)
		{
			TextureQualityIndex = CustomSettings->GetTextureQuality();
			SetQualitySwitcherWidget(TextureQualityIndex, TextureQualitySwitcher);
		}
		if (ShadowQualitySwitcher)
		{
			ShadowQualityIndex = CustomSettings->GetShadowQuality();
			SetQualitySwitcherWidget(ShadowQualityIndex, ShadowQualitySwitcher);
		}
		if (ShadingQualitySwitcher)
		{
			ShadingQualityIndex = CustomSettings->GetShadingQuality();
			SetQualitySwitcherWidget(ShadingQualityIndex, ShadingQualitySwitcher);
		}
		if (AntiAliasingQualitySwitcher)
		{
			AntiAliasingQualityIndex = CustomSettings->GetAntiAliasingQuality();
			SetQualitySwitcherWidget(AntiAliasingQualityIndex, AntiAliasingQualitySwitcher);
		}
		if (PostProcessQualitySwitcher)
		{
			PostProcessQualityIndex = CustomSettings->GetAntiAliasingQuality();
			SetQualitySwitcherWidget(PostProcessQualityIndex, PostProcessQualitySwitcher);
		}
		if (ViewDistanceQualitySwitcher)
		{
			ViewDistanceQualityIndex = CustomSettings->GetViewDistanceQuality();
			SetQualitySwitcherWidget(ViewDistanceQualityIndex, ViewDistanceQualitySwitcher);
		}
		if (VisualEffectsQualitySwitcher)
		{
			VisualEffectsQualityIndex = CustomSettings->GetVisualEffectQuality();
			SetQualitySwitcherWidget(VisualEffectsQualityIndex, VisualEffectsQualitySwitcher);
		}
		if (FoliageQualitySwitcher)
		{
			FoliageQualityIndex = CustomSettings->GetFoliageQuality();
			SetQualitySwitcherWidget(FoliageQualityIndex, FoliageQualitySwitcher);
		}
		if (FocalDistanceSwitcher)
		{
			bUseFocalDistance = CustomSettings->GetUseFocalDistanse();
			SetSwitcherBoolText(bUseFocalDistance, FocalDistanceSwitcher);
		}
	}
}

void USettingsGraphics::BindEvents()
{
	if (TextureQualitySwitcher)
	{
		TextureQualitySwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsGraphics::OnTextureQualitySwitcherLeftButtonClicked);
		TextureQualitySwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsGraphics::OnTextureQualitySwitcherRightButtonClicked);
	}
	if (ShadowQualitySwitcher)
	{
		ShadowQualitySwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsGraphics::OnShadowQualitySwitcherLeftButtonClicked);
		ShadowQualitySwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsGraphics::OnShadowQualitySwitcherRightButtonClicked);
	}
	if (ShadingQualitySwitcher)
	{
		ShadingQualitySwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsGraphics::OnShadingQualitySwitcherLeftButtonClicked);
		ShadingQualitySwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsGraphics::OnShadingQualitySwitcherRightButtonClicked);
	}
	if (AntiAliasingQualitySwitcher)
	{
		AntiAliasingQualitySwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsGraphics::OnAntiAliasingQualitySwitcherLeftButtonClicked);
		AntiAliasingQualitySwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsGraphics::OnAntiAliasingQualitySwitcherRightButtonClicked);
	}
	if (PostProcessQualitySwitcher)
	{
		PostProcessQualitySwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsGraphics::OnPostProcessQualitySwitcherLeftButtonClicked);
		PostProcessQualitySwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsGraphics::OnPostProcessQualitySwitcherRightButtonClicked);
	}
	if (ViewDistanceQualitySwitcher)
	{
		ViewDistanceQualitySwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsGraphics::OnViewDistanceQualitySwitcherLeftButtonClicked);
		ViewDistanceQualitySwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsGraphics::OnViewDistanceQualitySwitcherRightButtonClicked);
	}
	if (VisualEffectsQualitySwitcher)
	{
		VisualEffectsQualitySwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsGraphics::OnVisualEffectsQualitySwitcherLeftButtonClicked);
		VisualEffectsQualitySwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsGraphics::OnVisualEffectsQualitySwitcherRightButtonClicked);
	}
	if (FoliageQualitySwitcher)
	{
		FoliageQualitySwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsGraphics::OnFoliageQualitySwitcherLeftButtonClicked);
		FoliageQualitySwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsGraphics::OnFoliageQualitySwitcherRightButtonClicked);
	}
	if (FocalDistanceSwitcher)
	{
		FocalDistanceSwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsGraphics::OnFocalDistanceSwitcherLeftButtonClicked);
		FocalDistanceSwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsGraphics::OnFocalDistanceSwitcherRightButtonClicked);
	}
	if (ApplySettingsButton)
	{
		ApplySettingsButton->OnButtonClicked.AddDynamic(this, &USettingsGraphics::OnApplyGraphicsSettingsButtonClicked);
	}
}

bool USettingsGraphics::QualityAsText(FText& OutText, int32 Index)
{
	if (QualityIndexToTextMap.Contains(Index))
	{
		OutText = QualityIndexToTextMap[Index];
		return true;
	}
	else return false;
}

void USettingsGraphics::SetQualitySwitcherWidget(int32 QualityIndex, USettingsSwitcher* Switcher)
{
	if (Switcher)
	{
		FText QualityText;
		if (QualityAsText(QualityText, QualityIndex))
		{
			Switcher->SetOptionsTextBlock(QualityText);
		}
	}
}

void USettingsGraphics::SetSwitcherBoolText(bool State, USettingsSwitcher* Switcher)
{
	if (Switcher)
	{
		State ? Switcher->SetOptionsTextBlock(FText::FromString(TEXT("On"))) : Switcher->SetOptionsTextBlock(FText::FromString(TEXT("Off")));
	}
}

void USettingsGraphics::ChangeQualityIndex(int32& QualityIndex, int32 Delta, USettingsSwitcher* QualitySwitcher)
{
	QualityIndex = (QualityIndex + Delta + 5) % 5;
	SetQualitySwitcherWidget(QualityIndex, QualitySwitcher);
}

void USettingsGraphics::ChangeBoolSetting(bool& Setting, USettingsSwitcher* BoolSwitcher)
{
	Setting = !Setting;
	SetSwitcherBoolText(Setting, BoolSwitcher);
}

void USettingsGraphics::OnTextureQualitySwitcherLeftButtonClicked()
{
	ChangeQualityIndex(TextureQualityIndex, -1, TextureQualitySwitcher);
}

void USettingsGraphics::OnTextureQualitySwitcherRightButtonClicked()
{
	ChangeQualityIndex(TextureQualityIndex, 1, TextureQualitySwitcher);
}

void USettingsGraphics::OnShadowQualitySwitcherLeftButtonClicked()
{
	ChangeQualityIndex(ShadowQualityIndex, -1, ShadowQualitySwitcher);
}

void USettingsGraphics::OnShadowQualitySwitcherRightButtonClicked()
{
	ChangeQualityIndex(ShadowQualityIndex, 1, ShadowQualitySwitcher);
}

void USettingsGraphics::OnShadingQualitySwitcherLeftButtonClicked()
{
	ChangeQualityIndex(ShadingQualityIndex, -1, ShadingQualitySwitcher);
}

void USettingsGraphics::OnShadingQualitySwitcherRightButtonClicked()
{
	ChangeQualityIndex(ShadingQualityIndex, 1, ShadingQualitySwitcher);
}

void USettingsGraphics::OnAntiAliasingQualitySwitcherLeftButtonClicked()
{
	ChangeQualityIndex(AntiAliasingQualityIndex, -1, AntiAliasingQualitySwitcher);
}

void USettingsGraphics::OnAntiAliasingQualitySwitcherRightButtonClicked()
{
	ChangeQualityIndex(AntiAliasingQualityIndex, 1, AntiAliasingQualitySwitcher);
}

void USettingsGraphics::OnPostProcessQualitySwitcherLeftButtonClicked()
{
	ChangeQualityIndex(PostProcessQualityIndex, -1, PostProcessQualitySwitcher);
}

void USettingsGraphics::OnPostProcessQualitySwitcherRightButtonClicked()
{
	ChangeQualityIndex(PostProcessQualityIndex, 1, PostProcessQualitySwitcher);
}

void USettingsGraphics::OnViewDistanceQualitySwitcherLeftButtonClicked()
{
	ChangeQualityIndex(ViewDistanceQualityIndex, -1, ViewDistanceQualitySwitcher);
}

void USettingsGraphics::OnViewDistanceQualitySwitcherRightButtonClicked()
{
	ChangeQualityIndex(ViewDistanceQualityIndex, 1, ViewDistanceQualitySwitcher);
}

void USettingsGraphics::OnVisualEffectsQualitySwitcherLeftButtonClicked()
{
	ChangeQualityIndex(VisualEffectsQualityIndex, -1, VisualEffectsQualitySwitcher);
}

void USettingsGraphics::OnVisualEffectsQualitySwitcherRightButtonClicked()
{
	ChangeQualityIndex(VisualEffectsQualityIndex, 1, VisualEffectsQualitySwitcher);
}

void USettingsGraphics::OnFoliageQualitySwitcherLeftButtonClicked()
{
	ChangeQualityIndex(FoliageQualityIndex, -1, FoliageQualitySwitcher);
}

void USettingsGraphics::OnFoliageQualitySwitcherRightButtonClicked()
{
	ChangeQualityIndex(FoliageQualityIndex, 1, FoliageQualitySwitcher);
}

void USettingsGraphics::OnFocalDistanceSwitcherLeftButtonClicked()
{
	ChangeBoolSetting(bUseFocalDistance, FocalDistanceSwitcher);
}

void USettingsGraphics::OnFocalDistanceSwitcherRightButtonClicked()
{
	ChangeBoolSetting(bUseFocalDistance, FocalDistanceSwitcher);
}

void USettingsGraphics::OnApplyGraphicsSettingsButtonClicked()
{
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomSettings)
	{
		CustomSettings->SetTextureQuality(TextureQualityIndex);
		CustomSettings->SetShadowQuality(ShadowQualityIndex);
		CustomSettings->SetShadingQuality(ShadingQualityIndex);
		CustomSettings->SetAntiAliasingQuality(AntiAliasingQualityIndex);
		CustomSettings->SetPostProcessingQuality(PostProcessQualityIndex);
		CustomSettings->SetViewDistanceQuality(ViewDistanceQualityIndex);
		CustomSettings->SetVisualEffectQuality(VisualEffectsQualityIndex);
		CustomSettings->SetFoliageQuality(FoliageQualityIndex);
		CustomSettings->SetUseFocalDistanse(bUseFocalDistance);
		CustomSettings->ApplySettings(false);
	}
}


