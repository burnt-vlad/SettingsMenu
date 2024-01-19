// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Pause,
	GameOver
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchStateChanged, EMatchState, MatchState);

UCLASS()
class SETTINGSMENU_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnMatchStateChanged OnMatchStateChanged;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	UFUNCTION(BlueprintCallable)
	bool SetPauseHandle(APlayerController* PC);
	virtual bool ClearPause() override;
	UFUNCTION(BlueprintCallable)
	bool ClearPauseHandle();

protected:
	void SetMatchState(EMatchState State);

	EMatchState MatchState = EMatchState::WaitingToStart;
};
