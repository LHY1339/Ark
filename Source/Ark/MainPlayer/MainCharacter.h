#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ARK_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void Init_Default();
	void Init_Component();

public:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh_First;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh_Third;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera_First;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm_First;

};
