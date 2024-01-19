// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/HUDs/InGameHUD.h"
#include "Blueprint/UserWidget.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;
		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GetWorld())
	{
		const auto GameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddDynamic(this, &AInGameHUD::OnMatchStateChanged);
		}
	}
}

void AInGameHUD::OnMatchStateChanged(EMatchState MatchState)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GameWidgets.Contains(MatchState))
	{
		CurrentWidget = GameWidgets[MatchState];
	}
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}