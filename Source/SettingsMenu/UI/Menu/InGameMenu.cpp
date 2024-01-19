// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/Menu/InGameMenu.h"
#include "SettingsMenu/UI/Elements/BaseButton.h"
#include "Kismet/GameplayStatics.h"
#include "SettingsMenu/GameModes/BaseGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SettingsMenu/DataTypes.h"

void UInGameMenu::NativeConstruct()
{
	Super::NativeConstruct();
	BindEvents();
}

void UInGameMenu::BindEvents()
{
	if (ContinueButton)
	{
		ContinueButton->OnButtonClicked.AddUniqueDynamic(this, &UInGameMenu::OnContinueButtonClicked);
	}
	if (RestartButton)
	{
		RestartButton->OnButtonClicked.AddUniqueDynamic(this, &UInGameMenu::OnRestartButtonClicked);
	}
	if (SettingsButton)
	{
		SettingsButton->OnButtonClicked.AddUniqueDynamic(this, &UInGameMenu::OnSettingsButtonClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnButtonClicked.AddUniqueDynamic(this, &UInGameMenu::OnExitButtonClicked);
	}
}

void UInGameMenu::OnContinueButtonClicked()
{
	OnContinueButtonClickedDelegate.Broadcast();
	UWorld* World = GetWorld();
	if (World)
	{
		ABaseGameMode* GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(World));
		if (GameMode)
		{
			GameMode->ClearPause();
		}
	}
}

void UInGameMenu::OnRestartButtonClicked()
{
	OnRestartButtonClickedDelegate.Broadcast();
	UWorld* World = GetWorld();
	if (World)
	{
		FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(World);
		if (!CurrentLevelName.IsEmpty())
		{
			UGameplayStatics::OpenLevel(World, FName(*CurrentLevelName));
		}
	}
}

void UInGameMenu::OnSettingsButtonClicked()
{
	OnSettingsButtonClickedDelegate.Broadcast();
}

void UInGameMenu::OnMainMenuButtonClicked()
{
	OnMainMenuButtonClickedDelegate.Broadcast();
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName(LevelNames::MainMenuLevel));
	}
}

void UInGameMenu::OnExitButtonClicked()
{
	OnExitButtonClickedDelegate.Broadcast();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UKismetSystemLibrary::QuitGame(World, nullptr, EQuitPreference::Quit, false);
	}
}
