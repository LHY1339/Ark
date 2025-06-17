#pragma once

#include "CoreMinimal.h"
#include "Ark/Interface/IInteract.h"
#include "GameFramework/Actor.h"
#include "MainPickUp.generated.h"

class UBoxComponent;

UCLASS()
class ARK_API AMainPickUp : public AActor, public IIInteract
{
	GENERATED_BODY()

public:
	AMainPickUp();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Interact_Implementation(AMainCharacter* Character) override;
	virtual bool GetCanInteract_Implementation(AMainCharacter* Character) override;
	virtual void SetWidgetCharacter_Implementation(AMainCharacter* Character) override;
	virtual FPickUpProperty GetPickUpProperty_Implementation(AMainCharacter* Character) override;

private:
	void Init_Default();
	void Init_Component();

	virtual bool PickUpCond(AMainCharacter* Character, int& Num);
	virtual void PickUp(AMainCharacter* Character, int Num);
	virtual bool DropCond(AMainCharacter* Character, int& Num);
	virtual void Drop(AMainCharacter* Character, int Num);

	UFUNCTION()
	void OnRep_CanInteract();

	void SetCanInteract(bool NewCanInteract);
	
public:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Box_Collision;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Scene_AttachFirst;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Scene_AttachThird;

	UPROPERTY(ReplicatedUsing=OnRep_CanInteract)
	bool CanInteract = true;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Texture;

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Description;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor BackColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor TextColor;

	UPROPERTY()
	AMainCharacter* WidgetCharacter;
};
