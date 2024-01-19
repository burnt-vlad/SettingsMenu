// SettingsMenu / Fedosov Vladislav 


#include "SettingsMenu/PlayerControllers/MainMenuPlayerController.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
}
