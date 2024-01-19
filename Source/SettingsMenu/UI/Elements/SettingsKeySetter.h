// SettingsMenu / Fedosov Vladislav 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsKeySetter.generated.h"

class UOverlay;
class UHorizontalBox;
class UBorder;
class UTextBlock;
class UInputKeySelector;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeySelected, FInputChord, SelectedKey);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIsSelectedKeyChanged);

UCLASS()
class SETTINGSMENU_API USettingsKeySetter : public UUserWidget
{
	GENERATED_BODY()
	
public:
    USettingsKeySetter(const FObjectInitializer& ObjectInitializer);
    UInputKeySelector* GetKeySelector() const { return KeySelector; }

    //BlueprintAssignable delegates for key events
    UPROPERTY(BlueprintAssignable)
    FOnKeySelected OnKeySelected;
    UPROPERTY(BlueprintAssignable)
    FOnIsSelectedKeyChanged OnIsSelectedKeyChanged;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText OptionTextToDisplay;

protected:
    virtual void NativeConstruct() override;
    void NativePreConstruct() override;
    void BindEvents();
    void SetDefaultOptionText();

    // Event handler functions
    UFUNCTION()
    void OnKeySelectedHandler(FInputChord InSelectedKey);
    UFUNCTION()
    void OnIsSelectedKeyChangedHandler();

    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionTextBlock;
    UPROPERTY(meta = (BindWidget))
    UInputKeySelector* KeySelector;
};
