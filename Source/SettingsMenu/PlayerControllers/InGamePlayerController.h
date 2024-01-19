// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "SettingsMenu/PlayerControllers/BasePlayerController.h"
#include "SettingsMenu/GameModes/BaseGameMode.h"
#include "InGamePlayerController.generated.h"

UCLASS()
class SETTINGSMENU_API AInGamePlayerController : public ABasePlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	// Movement functions
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnUp(float Amount);
	void TurnRight(float Amount);
	void StartJumping();
	void StopJumping();

	// Multiplier for mouse sensitivity
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Input")
	float MouseSensitivityMultiplier = 1.f;
	UFUNCTION()
	void UpdateMouseSensitivityMultiplier(float Multiplier);
	// Flag for inverting the X-axis mouse movement
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Input")
	bool MouseXInvertation;
	UFUNCTION()
	void UpdateMouseXInvertation(bool State) { MouseXInvertation = State; }
	// Flag for inverting the Y-axis mouse movement
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Input")
	bool MouseYInvertation;
	UFUNCTION()
	void UpdateMouseYInvertation(bool State) { MouseYInvertation = State; }

	TSoftObjectPtr<class AInGameCharacter> ControlledPlayerCharacter;

private:
	void PauseGame();
	UFUNCTION()
	void OnMatchStateChanged(EMatchState State);
};
