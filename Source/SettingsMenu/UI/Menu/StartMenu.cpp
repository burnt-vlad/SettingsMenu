// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Menu/StartMenu.h"
#include "Components/HorizontalBox.h"
#include "Components/Overlay.h"
#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "SettingsMenu/DataTypes.h"
#include "Kismet/GameplayStatics.h"

void UStartMenu::NativeConstruct()
{
	Super::NativeConstruct();
	BindEvents();
}

void UStartMenu::BindEvents()
{
	if (PlayButton)
	{
		PlayButton->OnButtonClicked.AddUniqueDynamic(this, &UStartMenu::OnPlayButtonClicked);
	}
	if (SettingsButton)
	{
		SettingsButton->OnButtonClicked.AddUniqueDynamic(this, &UStartMenu::OnSettingsButtonClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnButtonClicked.AddUniqueDynamic(this, &UStartMenu::OnExitButtonClicked);
	}
}

void UStartMenu::OnPlayButtonClicked()
{
	OnPlayButtonClickedDelegate.Broadcast();
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName(LevelNames::MainLevel));
	}
}

void UStartMenu::OnSettingsButtonClicked()
{
	OnSettingsButtonClickedDelegate.Broadcast();
}

void UStartMenu::OnExitButtonClicked()
{
	OnExitButtonClickedDelegate.Broadcast();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UKismetSystemLibrary::QuitGame(World, nullptr, EQuitPreference::Quit, false);
	}
}
