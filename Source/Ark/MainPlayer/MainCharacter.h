#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ark/Object/MainPlayerObject.h"
#include "MainCharacter.generated.h"

class ULimitComponent;
class AMainGameStateBase;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ARK_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//Override
	AMainCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Input
	void Input_MoveForward(float Value);
	void Input_MoveRight(float Value);
	void Input_LookUp(float Value);
	void Input_LookRight(float Value);
	void Input_JumpPress();
	void Input_JumpRelease();
	void Input_RunPress();
	void Input_RunRelease();
	void Input_CrouchPress();

	//Custom
	FAnimVariable GetAnimVariable();

private:
	//Init
	void Init_Default();
	void Init_Component();
	void Init_Value();

	//BeginPlay
	void Begin_Bind();

	//Tick
	void Tick_Calculate(float DeltaTime);
	void Tick_Update(float DeltaTime);
	void Tick_Smooth(float DeltaTime);
	void Tick_Camera(float DeltaTime);
	void Tick_Crouch(float DeltaTime);

	//Custom
	float GetServerDeltaTime();
	void SetCrouch(bool NewCrouch);

	//RPC
	UFUNCTION(Server, Unreliable)
	void UpdateVariable_Server(FUpdateVariable Var);

	//Reflection
	UFUNCTION()
	void OnRep_Crouch();

public:
	//Components
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh_First;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh_Third;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera_First;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm_First;

	UPROPERTY(EditDefaultsOnly)
	ULimitComponent* Limit_Speed;

	//Movement
	UPROPERTY(Replicated)
	float Rep_Speed;

	UPROPERTY(Replicated)
	float Rep_AirSpeed;

	UPROPERTY(Replicated)
	float Rep_Direction;

	UPROPERTY(Replicated)
	float Rep_Pitch;

	UPROPERTY(Replicated)
	FVector Rep_Location;

	UPROPERTY(Replicated)
	FRotator Rep_Rotation;

	UPROPERTY(ReplicatedUsing=OnRep_Crouch)
	bool Rep_Crouch = false;

	UPROPERTY(Replicated)
	bool Rep_UseSmooth = false;

	bool CanMove = true;
	bool CanTurn = true;

	UPROPERTY()
	AMainGameStateBase* GameState;
};
