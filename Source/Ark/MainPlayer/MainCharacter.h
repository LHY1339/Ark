#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ark/Object/MainPlayerObject.h"
#include "MainCharacter.generated.h"

class AMainPlayerController;
class UBoxComponent;
class UUW_MainPlayer;
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
	void Input_InteractPress();

	//Custom
	FAnimVariable GetAnimVariable();

	bool AddInteractActor(AActor* NewActor);
	void RemoveInteractActor(AActor* Actor);

	void OnPawnLeavingGame(AMainPlayerController* PlayerController);

private:
	//Init
	void Init_Default();
	void Init_Component();
	void Init_Value();

	//BeginPlay
	void Begin_Bind();
	void Begin_Widget();

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

	UFUNCTION(Server, Unreliable)
	void Interact_Server(AActor* InteractActor);

	//Reflection
	UFUNCTION()
	void OnRep_Crouch();

	UFUNCTION()
	void Box_Interact_BeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void Box_Interact_EndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

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
	UStaticMeshComponent* StaticMesh_Interact;

	UPROPERTY(EditDefaultsOnly)
	ULimitComponent* Limit_Speed;

	//Blueprint
	UPROPERTY(EditDefaultsOnly, Category="Class")
	TSubclassOf<UUW_MainPlayer> MainPlayerWidgetClass;

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

	UPROPERTY()
	AMainGameStateBase* GameState;

	UPROPERTY()
	UUW_MainPlayer* MainPlayerWidget;

	UPROPERTY()
	TArray<AActor*> InteractList;

	UPROPERTY(Replicated)
	TArray<AActor*> PickUpList;

	UPROPERTY(Replicated)
	TArray<AActor*> WeaponList;

	bool CanMove = true;
	bool CanTurn = true;
};
