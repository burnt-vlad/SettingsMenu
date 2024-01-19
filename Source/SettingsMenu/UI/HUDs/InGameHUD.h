// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SettingsMenu/GameModes/BaseGameMode.h"
#include "InGameHUD.generated.h"

class UUserWidget;

UCLASS()
class SETTINGSMENU_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnMatchStateChanged(EMatchState MatchState);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>PlayerHUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>PauseWidgetClass;

	UPROPERTY()
	TMap<EMatchState, UUserWidget*> GameWidgets;
	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;
};
