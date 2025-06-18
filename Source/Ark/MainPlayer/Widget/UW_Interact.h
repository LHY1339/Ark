#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Interact.generated.h"


class AMainCharacter;
class UImage;
class UTextBlock;
class UButton;

UCLASS()
class ARK_API UUW_Interact : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetCharacter(AMainCharacter* Character);

public:
	UPROPERTY(Meta = (BindWidget))
	UButton* Button_Base;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* TextBlock_Name;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* TextBlock_Description;

	UPROPERTY(Meta = (BindWidget))
	UImage* Image_Texture;

	UPROPERTY(Meta = (BindWidget))
	UImage* Image_BK;

	UPROPERTY()
	AActor* InteractActor;

	UPROPERTY()
	AMainCharacter* OwningCharacter;
};
