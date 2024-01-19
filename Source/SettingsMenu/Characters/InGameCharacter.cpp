// SettingsMenu / Fedosov Vladislav 

#include "SettingsMenu/Characters/InGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "SettingsMenu/GameUserSettings/CustomGameUserSettings.h"

AInGameCharacter::AInGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCamera->SetupAttachment(GetRootComponent());
	FirstPersonCamera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	FirstPersonCamera->bUsePawnControlRotation = true;
}

void AInGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	UCustomGameUserSettings* CustomGameUserSettings = UCustomGameUserSettings::GetCustomGameUserSettings();
	if (CustomGameUserSettings)
	{
		CustomGameUserSettings->OnFocalDistanseStateChanged.AddDynamic(this, &AInGameCharacter::UseFocalDistance);
		bUseFocalDistance = CustomGameUserSettings->GetUseFocalDistanse();
	}
}

void AInGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateFocalDistance();
}

void AInGameCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AInGameCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void AInGameCharacter::TurnUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void AInGameCharacter::TurnRight(float Amount)
{
	AddControllerYawInput(Amount);
}

void AInGameCharacter::OnStartJumping()
{
	Jump();
}

void AInGameCharacter::OnStopJumping()
{
	StopJumping();
}

void AInGameCharacter::UpdateFocalDistance()
{
	if (bUseFocalDistance)
	{
		SetCameraFocalDistance();
	}
}

void AInGameCharacter::SetCameraFocalDistance()
{
	float CameraTraceDistance = GetCameraTraceDistance();
	FirstPersonCamera->PostProcessSettings.DepthOfFieldFocalDistance = CameraTraceDistance;
}

float AInGameCharacter::GetCameraTraceDistance()
{
	if (!GetWorld() || !FirstPersonCamera) return 0.f;
	FHitResult CameraTraceHit;
	FVector TraceStart = FirstPersonCamera->GetComponentLocation();
	FVector TraceEnd = TraceStart + FirstPersonCamera->GetForwardVector() * 100000.f;;
	GetWorld()->LineTraceSingleByChannel(CameraTraceHit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	if (CameraTraceHit.bBlockingHit)
	{
		return (CameraTraceHit.Location - FirstPersonCamera->GetComponentLocation()).Size();
	}
	return 0.f;
}

void AInGameCharacter::UseFocalDistance(bool State)
{
	bUseFocalDistance = State;
	FirstPersonCamera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = State;
}

