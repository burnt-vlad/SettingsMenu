// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "SettingsMenu/PlayerControllers/BasePlayerController.h"
#include "MainMenuPlayerController.generated.h"

UCLASS()
class SETTINGSMENU_API AMainMenuPlayerController : public ABasePlayerController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
};
