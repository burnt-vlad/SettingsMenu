// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/UI/HUDs/MainMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MenuWidgetClass)
	{
		const auto MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}