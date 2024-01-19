// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InGameCharacter.generated.h"

UCLASS()
class SETTINGSMENU_API AInGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AInGameCharacter();
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnUp(float Amount);
	void TurnRight(float Amount);
	void OnStartJumping();
	void OnStopJumping();

protected:
	virtual void BeginPlay() override;
	void UpdateFocalDistance();
	void SetCameraFocalDistance();
	float GetCameraTraceDistance();
	UFUNCTION()
	void UseFocalDistance(bool State);

	//Flag indicating whether the camera will focus on nearby objects.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	bool bUseFocalDistance = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FirstPersonCamera;
};
