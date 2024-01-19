// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/GameModes/BaseGameMode.h"

DEFINE_LOG_CATEGORY_STATIC(BaseGameMode, All, All);

void ABaseGameMode::StartPlay()
{
	Super::StartPlay();
	SetMatchState(EMatchState::InProgress);
}

bool ABaseGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const bool PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	SetMatchState(EMatchState::Pause);
	return PauseSet;
}

bool ABaseGameMode::SetPauseHandle(APlayerController* PC)
{
	return SetPause(PC);
}

bool ABaseGameMode::ClearPause()
{
	const bool PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(EMatchState::InProgress);
	}
	return PauseCleared;
}

bool ABaseGameMode::ClearPauseHandle()
{
	return ClearPause();
}

void ABaseGameMode::SetMatchState(EMatchState State)
{
	if (MatchState == State) return;
	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}