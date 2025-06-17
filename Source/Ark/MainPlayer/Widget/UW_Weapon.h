#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Weapon.generated.h"


class AMainCharacter;
class UButton;
class UImage;
class UTextBlock;

UCLASS()
class ARK_API UUW_Weapon : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void SetCharacter(AMainCharacter* Character);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Key;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Icon;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Base;
	
	UPROPERTY(EditAnywhere)
	int Index = 0;

private:
	UPROPERTY()
	AMainCharacter* OwningCharacter;
};
