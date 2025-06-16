#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_MainPlayer.generated.h"

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

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUW_Interact> InteractWidgetClass;
	
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_Interact;
	
};
