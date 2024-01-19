// SettingsMenu / Fedosov Vladislav 


#include "SettingsMenu/PlayerControllers/InGamePlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "SettingsMenu/Characters/InGameCharacter.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"

void AInGamePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	ControlledPlayerCharacter = Cast<AInGameCharacter>(InPawn);
	MouseXInvertation = false;
	MouseYInvertation = false;
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &AInGamePlayerController::PauseGame);
	InputComponent->BindAxis("MoveForward", this, &AInGamePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AInGamePlayerController::MoveRight);
	InputComponent->BindAxis("TurnUp", this, &AInGamePlayerController::TurnUp);
	InputComponent->BindAxis("TurnRight", this, &AInGamePlayerController::TurnRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AInGamePlayerController::StartJumping);
	InputComponent->BindAction("Jump", IE_Released, this, &AInGamePlayerController::StopJumping);
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		const auto GameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddDynamic(this, &AInGamePlayerController::OnMatchStateChanged);
		}
	}
	UCustomGameUserSettings* CustomGameUserSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomGameUserSettings)
	{
		CustomGameUserSettings->OnMouseSensitivityMultiplierChanged.AddDynamic(this, &AInGamePlayerController::UpdateMouseSensitivityMultiplier);
		MouseSensitivityMultiplier = CustomGameUserSettings->GetMouseSensitivityMultiplier();
		CustomGameUserSettings->OnMouseXInvertationChanged.AddDynamic(this, &AInGamePlayerController::UpdateMouseXInvertation);
		MouseXInvertation = CustomGameUserSettings->GetMouseXInvertation();
		CustomGameUserSettings->OnMouseYInvertationChanged.AddDynamic(this, &AInGamePlayerController::UpdateMouseYInvertation);
		MouseYInvertation = CustomGameUserSettings->GetMouseYInvertation();
	}
	if (!ControlledPlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("ControlledPlayerCharacter is not valid"));
	}
}

void AInGamePlayerController::MoveForward(float Amount)
{
	if (ControlledPlayerCharacter.IsValid())
	{
		ControlledPlayerCharacter->MoveForward(Amount);
	}
}

void AInGamePlayerController::MoveRight(float Amount)
{
	if (ControlledPlayerCharacter.IsValid())
	{
		ControlledPlayerCharacter->MoveRight(Amount);
	}
}

void AInGamePlayerController::TurnUp(float Amount)
{
	if (ControlledPlayerCharacter.IsValid())
	{
		float InvertedAmount = MouseYInvertation ? Amount : -Amount;
		ControlledPlayerCharacter->TurnUp(InvertedAmount * MouseSensitivityMultiplier);
	}
}

void AInGamePlayerController::TurnRight(float Amount)
{
	if (ControlledPlayerCharacter.IsValid())
	{
		float InvertedAmount = MouseXInvertation ? -Amount : Amount;
		ControlledPlayerCharacter->TurnRight(InvertedAmount * MouseSensitivityMultiplier);
	}
}

void AInGamePlayerController::StartJumping()
{
	if (ControlledPlayerCharacter.IsValid())
	{
		ControlledPlayerCharacter->OnStartJumping();
	}
}

void AInGamePlayerController::StopJumping()
{
	if (ControlledPlayerCharacter.IsValid())
	{
		ControlledPlayerCharacter->OnStopJumping();
	}
}

void AInGamePlayerController::PauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AInGamePlayerController::OnMatchStateChanged(EMatchState State)
{
	if (State == EMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void AInGamePlayerController::UpdateMouseSensitivityMultiplier(float Multiplier)
{
	MouseSensitivityMultiplier = FMath::Clamp(Multiplier, 0.f, 1.f);
}
