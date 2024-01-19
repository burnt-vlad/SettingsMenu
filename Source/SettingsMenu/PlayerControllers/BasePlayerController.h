// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"
#include "BasePlayerController.generated.h"

UCLASS()
class SETTINGSMENU_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	void SetupSoundMix(const FString& SoundMixName, const FString& SoundClassName, UCustomGameUserSettings* CustomSettings, float (UCustomGameUserSettings::* VolumeFunction)() const);
};
