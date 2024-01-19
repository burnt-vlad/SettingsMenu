// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/SettingsWidgets/SettingsDisplay.h"
#include "SettingsMenu/UI/Elements/SettingsSwitcher.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Components/Spacer.h"
#include "Application/SlateApplicationBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"
#include "Internationalization/TextLocalizationManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogSettingsDisplay, All, All);

USettingsDisplay::USettingsDisplay(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultResolutions.Add(FIntPoint(1366, 768));
	DefaultResolutions.Add(FIntPoint(1440, 900));
	DefaultResolutions.Add(FIntPoint(1660, 900));
	DefaultResolutions.Add(FIntPoint(1920, 1080));
	DefaultResolutions.Add(FIntPoint(2560, 1440));
	DefaultResolutions.Add(FIntPoint(2560, 1600));
	DefaultResolutions.Add(FIntPoint(3440, 1440));
	DefaultResolutions.Add(FIntPoint(3840, 1440));

	SupportedFrameRates.Add(30.0f);
	SupportedFrameRates.Add(60.0f);
	SupportedFrameRates.Add(120.0f);
	SupportedFrameRates.Add(144.0f);
	SupportedFrameRates.Add(240.0f);
	SupportedFrameRates.Add(0.0f);
} 

void USettingsDisplay::NativeConstruct()
{
	Super::NativeConstruct();
	BindEvents();
	HandleLanguageSwitcher();
	UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomSettings)
	{
		HandleWindowModeSwitcher(CustomSettings);
		HandleResolutionSwitcher(CustomSettings);
		HandleFrameRateSwitcher(CustomSettings);
		HandleVSyncSwitcher(CustomSettings);
	}
	SupportedResolutions = GetSupportedResolutions(WindowMode);
}

void USettingsDisplay::BindEvents()
{
	if (LanguageSwitcher)
	{
		LanguageSwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsDisplay::OnLanguageSwitcherLeftButtonClicked);
		LanguageSwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsDisplay::OnLanguageSwitcherRightButtonClicked);
	}
	if (WindowModeSwitcher)
	{
		WindowModeSwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsDisplay::OnWindowModeSwitcherLeftButtonClicked);
		WindowModeSwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsDisplay::OnWindowModeSwitcherRightButtonClicked);
	}
	if (ResolutionSwitcher)
	{
		ResolutionSwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsDisplay::OnResolutionSwitcherLeftButtonClicked);
		ResolutionSwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsDisplay::OnResolutionSwitcherRightButtonClicked);
	}
	if (FrameRateSwitcher)
	{
		FrameRateSwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsDisplay::OnFrameRateSwitcherLeftButtonClicked);
		FrameRateSwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsDisplay::OnFrameRateSwitcherRightButtonClicked);
	}
	if (VSyncSwitcher)
	{
		VSyncSwitcher->OnLeftButtonClicked.AddDynamic(this, &USettingsDisplay::OnVSyncSwitcherLeftButtonClicked);
		VSyncSwitcher->OnRightButtonClicked.AddDynamic(this, &USettingsDisplay::OnVSyncSwitcherRightButtonClicked);
	}
	if (ApplySettingsButton)
	{
		ApplySettingsButton->OnButtonClicked.AddDynamic(this, &USettingsDisplay::OnApplySettingsButtonClicked);
	}
}

FText USettingsDisplay::GetWindowModeAsText() const
{
	switch (WindowMode)
	{
	case EWindowMode::Fullscreen:
		return FText::FromString(TEXT("Fullscreen"));
	case EWindowMode::WindowedFullscreen:
		return FText::FromString(TEXT("Full Window"));
	case EWindowMode::Windowed:
		return FText::FromString(TEXT("Windowed"));
	default:
		UE_LOG(LogSettingsDisplay, Error, TEXT("Unknown window mode. Check window modes"));
		return FText::FromString(TEXT("Unknown"));
	}
}

void USettingsDisplay::SetSwitcherResolutionText(FIntPoint InScreenResolution, USettingsSwitcher* Switcher)
{
	if (Switcher)
	{
		FNumberFormattingOptions NoCommasOptions;
		NoCommasOptions.UseGrouping = false;

		FText XResText = FText::AsNumber(InScreenResolution.X, &NoCommasOptions);
		FText YResText = FText::AsNumber(InScreenResolution.Y, &NoCommasOptions);

		FText ResolutionText = FText::Format(NSLOCTEXT("UI", "Resolution", "{0} x {1}"), XResText, YResText);
		Switcher->SetOptionsTextBlock(ResolutionText);
	}
}

void USettingsDisplay::SetSwitcherBoolText(bool State, USettingsSwitcher* Switcher)
{
	if (Switcher)
	{
		State ? Switcher->SetOptionsTextBlock(FText::FromString(TEXT("On"))) : Switcher->SetOptionsTextBlock(FText::FromString(TEXT("Off")));
	}
}

void USettingsDisplay::HandleLanguageSwitcher()
{
	if (LanguageSwitcher)
	{
		FInternationalization& Internationalization = FInternationalization::Get();
		TArray<FCultureRef> AvailableCulturesRef = Internationalization.GetAvailableCultures(AvailableCultureCodes, false);
		CurrentLanguageCode = Internationalization.GetCurrentCulture()->GetName();
		FString DisplayName = Internationalization.GetCurrentCulture()->GetDisplayName();
		FText DisplayText = FText::FromString(DisplayName);
		LanguageSwitcher->SetOptionsTextBlock(DisplayText);
	}
}

void USettingsDisplay::HandleWindowModeSwitcher(UCustomGameUserSettings* CustomSettings)
{
	if (WindowModeSwitcher)
	{
		WindowMode = CustomSettings->GetFullscreenMode();
		WindowModeSwitcher->SetOptionsTextBlock(GetWindowModeAsText());
	}
}

void USettingsDisplay::HandleResolutionSwitcher(UCustomGameUserSettings* CustomSettings)
{
	if (ResolutionSwitcher)
	{
		ScreenResolution = CustomSettings->GetScreenResolution();
		SetSwitcherResolutionText(ScreenResolution, ResolutionSwitcher);
	}
}

void USettingsDisplay::HandleFrameRateSwitcher(UCustomGameUserSettings* CustomSettings)
{
	if (FrameRateSwitcher)
	{
		FrameRateLimit = CustomSettings->GetFrameRateLimit();
		if (FrameRateLimit == 0)
		{
			FrameRateSwitcher->SetOptionsTextBlock(FText::FromString(TEXT("Unlimited")));
		}
		else
		{
			FrameRateSwitcher->SetOptionsTextBlock(FText::AsNumber(FrameRateLimit));
		}
	}
}

void USettingsDisplay::HandleVSyncSwitcher(UCustomGameUserSettings* CustomSettings)
{
	if (VSyncSwitcher)
	{
		bEnableVSync = CustomSettings->IsVSyncEnabled();
		SetSwitcherBoolText(bEnableVSync, VSyncSwitcher);
	}
}

FText USettingsDisplay::ConvertLanguageCodeToDisplayText(const FString& LanguageCode)
{
	FCulturePtr CulturePtr = FInternationalization::Get().GetCulture(LanguageCode);
	if (CulturePtr.IsValid())
	{
		FString DisplayName = CulturePtr->GetDisplayName();
		return FText::FromString(DisplayName);
	}
	else
	{
		UE_LOG(LogSettingsDisplay, Error, TEXT("ConvertLanguageCodeToDisplayName() fail, check language code"));
		return FText::FromString(TEXT("English"));
	}
}

TArray<FIntPoint> USettingsDisplay::GetSupportedResolutions(EWindowMode::Type InWindowMode)
{
	TArray<FIntPoint> DisplaySupportedResolutions;
	switch (InWindowMode)
	{
	case EWindowMode::Fullscreen:
		UKismetSystemLibrary::GetSupportedFullscreenResolutions(DisplaySupportedResolutions);
		break;
	case EWindowMode::WindowedFullscreen:
		UKismetSystemLibrary::GetConvenientWindowedResolutions(DisplaySupportedResolutions);
		break;
	case EWindowMode::Windowed:
		UKismetSystemLibrary::GetConvenientWindowedResolutions(DisplaySupportedResolutions);
		break;
	default:
		DisplaySupportedResolutions = DefaultResolutions;
		UE_LOG(LogSettingsDisplay, Error, TEXT("Unknown window mode. Check window modes."));
		break;
	}
	return DisplaySupportedResolutions;
}

void USettingsDisplay::ChangeLanguage(int32 Delta)
{
	if (LanguageSwitcher)
	{
		int32 Index = AvailableCultureCodes.Find(CurrentLanguageCode);
		int32 NumElements = AvailableCultureCodes.Num();

		if (Index != INDEX_NONE)
		{
			Index = (Index + Delta + NumElements) % NumElements;
			CurrentLanguageCode = AvailableCultureCodes[Index];
			FText NewLanguageDisplayText = ConvertLanguageCodeToDisplayText(CurrentLanguageCode);
			LanguageSwitcher->SetOptionsTextBlock(NewLanguageDisplayText);
		}
	}
}

void USettingsDisplay::ChangeWindowMode(int32 Delta)
{
	if (WindowModeSwitcher)
	{
		int32 Index = static_cast<int32>(WindowMode);
		int32 NumElements = static_cast<int32>(EWindowMode::Windowed);
		WindowMode = static_cast<EWindowMode::Type>((Index + Delta + 3) % 3);
		WindowModeSwitcher->SetOptionsTextBlock(GetWindowModeAsText());
	}
}

void USettingsDisplay::ChangeScreenResolution(int32 Delta)
{
	if (ResolutionSwitcher)
	{
		int32 NumElements = SupportedResolutions.Num();
		if (NumElements == 0)
		{
			UE_LOG(LogSettingsDisplay, Error, TEXT("Unable to access available screen resolutions."));
			SupportedResolutions = DefaultResolutions;
			NumElements = SupportedResolutions.Num();
		}

		int32 Index = SupportedResolutions.IndexOfByKey(ScreenResolution);
		if (Index == INDEX_NONE)
		{
			SupportedResolutions = DefaultResolutions;
		}

		Index = (Index + Delta + NumElements) % NumElements;
		ScreenResolution = SupportedResolutions[Index];
		SetSwitcherResolutionText(ScreenResolution, ResolutionSwitcher);
	}
}

void USettingsDisplay::ChangeFrameRateLimit(int32 Delta)
{
	if (FrameRateSwitcher)
	{
		int32 NumElements = SupportedFrameRates.Num();
		int32 Index = SupportedFrameRates.Find(FrameRateLimit);
		if (Index != INDEX_NONE)
		{
			Index = (Index + Delta + NumElements) % NumElements;
			FrameRateLimit = SupportedFrameRates[Index];

			if (FrameRateLimit != 0.f)
			{
				FrameRateSwitcher->SetOptionsTextBlock(FText::AsNumber(FrameRateLimit));
			}
			else
			{
				FrameRateSwitcher->SetOptionsTextBlock(FText::FromString(TEXT("Unlimited")));
			}
		}
	}
}

void USettingsDisplay::OnLanguageSwitcherLeftButtonClicked()
{
	ChangeLanguage(-1);
}

void USettingsDisplay::OnLanguageSwitcherRightButtonClicked()
{
	ChangeLanguage(1);
}

void USettingsDisplay::OnWindowModeSwitcherLeftButtonClicked()
{
	ChangeWindowMode(-1);
}

void USettingsDisplay::OnWindowModeSwitcherRightButtonClicked()
{
	ChangeWindowMode(1);
}

void USettingsDisplay::OnResolutionSwitcherLeftButtonClicked()
{
	ChangeScreenResolution(-1);
}

void USettingsDisplay::OnResolutionSwitcherRightButtonClicked()
{
	ChangeScreenResolution(1);
}

void USettingsDisplay::OnFrameRateSwitcherLeftButtonClicked()
{
	ChangeFrameRateLimit(-1);
}

void USettingsDisplay::OnFrameRateSwitcherRightButtonClicked()
{
	ChangeFrameRateLimit(1);
}

void USettingsDisplay::OnVSyncSwitcherLeftButtonClicked()
{
	if (VSyncSwitcher)
	{
		bEnableVSync = !bEnableVSync;
		SetSwitcherBoolText(bEnableVSync, VSyncSwitcher);
	}
}

void USettingsDisplay::OnVSyncSwitcherRightButtonClicked()
{
	if (VSyncSwitcher)
	{
		bEnableVSync = !bEnableVSync;
		SetSwitcherBoolText(bEnableVSync, VSyncSwitcher);
	}
}

void USettingsDisplay::OnApplySettingsButtonClicked()
{
	if (ApplySettingsButton)
	{
		UCustomGameUserSettings* CustomSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
		if (CustomSettings)
		{
			CustomSettings->SetFullscreenMode(WindowMode);
			CustomSettings->SetScreenResolution(ScreenResolution);
			CustomSettings->SetFrameRateLimit(FrameRateLimit);
			CustomSettings->SetVSyncEnabled(bEnableVSync);
			CustomSettings->ApplySettings(false);
		}
	}
}

