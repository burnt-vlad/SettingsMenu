// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsSwitcher.generated.h"

class UHorizontalBox;
class UBorder;
class UTextBlock;
class UBaseButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRightButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftButtonClicked);

UCLASS()
class SETTINGSMENU_API USettingsSwitcher : public UUserWidget
{
	GENERATED_BODY()

public:
    USettingsSwitcher(const FObjectInitializer& ObjectInitializer);
    void SetOptionsTextBlock(FText TextToDisplay);

    // BlueprintAssignable delegates for key-related events
    UPROPERTY(BlueprintAssignable)
    FOnRightButtonClicked OnRightButtonClicked;
    UPROPERTY(BlueprintAssignable)
    FOnLeftButtonClicked OnLeftButtonClicked;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText OptionTextToDisplay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText OptionsTextToDisplay;

protected:
    virtual void NativeConstruct() override;
    virtual void NativePreConstruct() override;
    void BindEvents();

    // Event handler functions
    UFUNCTION()
    void OnSwitcherRightButtonClicked();
    UFUNCTION()
    void OnSwitcherLeftButtonClicked();

    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionTextBlock;
    UPROPERTY(meta = (BindWidget))
    UBaseButton* LeftButton;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionsTextBlock;
    UPROPERTY(meta = (BindWidget))
    UBaseButton* RightButton;

};
