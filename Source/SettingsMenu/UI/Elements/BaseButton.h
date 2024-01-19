// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonUnhovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReleased);

UCLASS()
class SETTINGSMENU_API UBaseButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UBaseButton(const FObjectInitializer& ObjectInitializer);

    // BlueprintAssignable delegates for button events
    UPROPERTY(BlueprintAssignable)
    FOnButtonClicked OnButtonClicked;
    UPROPERTY(BlueprintAssignable)
    FOnButtonHovered OnButtonHovered;
    UPROPERTY(BlueprintAssignable)
    FOnButtonUnhovered OnButtonUnhovered;
    UPROPERTY(BlueprintAssignable)
    FOnButtonPressed OnButtonPressed;
    UPROPERTY(BlueprintAssignable)
    FOnButtonReleased OnButtonReleased;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ButtonTextToDisplay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InnerBorderTopPadding;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InnerBorderBottomPadding;

protected:
    void NativePreConstruct();
    virtual void NativeConstruct() override;
    void BindEvents();
    void SetDefaultButtonText();

    // Event handler functions
    UFUNCTION()
    void OnBaseButtonClicked();
    UFUNCTION()
    void OnBaseButtonHovered();
    UFUNCTION()
    void OnBaseButtonUnhovered();
    UFUNCTION()
    void OnBaseButtonPressed();
    UFUNCTION()
    void OnBaseButtonReleased();

    UPROPERTY(meta = (BindWidget))
    class UButton* VolumeButton;
    UPROPERTY(meta = (BindWidget))
    class UBorder* InnerBorder;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ButtonTextBlock;
};
