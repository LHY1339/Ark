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

private:
	void Init_Default();
	void Init_Component();

	virtual bool PickUpCond(AMainCharacter* Character, int& Num);
	virtual void PickUp(AMainCharacter* Character, int Num);
	virtual bool DropCond(AMainCharacter* Character, int& Num);
	virtual void Drop(AMainCharacter* Character, int Num);

public:
	UPROPERTY(Replicated)
	bool CanInteract = true;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Box_Collision;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Scene_AttachFirst;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Scene_AttachThird;
};
