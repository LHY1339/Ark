#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_MainPlayer.generated.h"

class UUW_Weapon;
class AMainCharacter;
class UUW_PickUp;
class UUW_Interact;
class UScrollBox;

UCLASS()
class ARK_API UUW_MainPlayer : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddActorToInteractList(AActor* NewActor);
	void RemoveActorFromInteractList(AActor* Actor);
	void FlushInteractList();

	void SetCharacter(AMainCharacter* Character);

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUW_Interact> InteractWidgetClass;
	
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_Interact;

	UPROPERTY(meta = (BindWidget))
	UUW_PickUp* UMG_PickUp_1;
	
	UPROPERTY(meta = (BindWidget))
	UUW_PickUp* UMG_PickUp_2;
	
	UPROPERTY(meta = (BindWidget))
	UUW_PickUp* UMG_PickUp_3;
	
	UPROPERTY(meta = (BindWidget))
	UUW_PickUp* UMG_PickUp_4;

	UPROPERTY(meta = (BindWidget))
	UUW_PickUp* UMG_PickUp_5;

	UPROPERTY(meta = (BindWidget))
	UUW_Weapon* UMG_Weapon_1;

	UPROPERTY(meta = (BindWidget))
	UUW_Weapon* UMG_Weapon_2;

private:
	AMainCharacter* OwningCharacter;
};
