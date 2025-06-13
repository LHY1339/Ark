#include "MainCharacter.h"

#include "MainGameStateBase.h"
#include "Camera/CameraComponent.h"
#include "Component/LimitComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

AMainCharacter::AMainCharacter()
{
	Init_Default();
	Init_Component();
	Init_Value();
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMainCharacter::Input_MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMainCharacter::Input_MoveRight);
	InputComponent->BindAxis("LookUp", this, &AMainCharacter::Input_LookUp);
	InputComponent->BindAxis("LookRight", this, &AMainCharacter::Input_LookRight);

	InputComponent->BindAction("Run", IE_Pressed, this, &AMainCharacter::Input_RunPress);
	InputComponent->BindAction("Run", IE_Released, this, &AMainCharacter::Input_RunRelease);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Input_JumpPress);
	InputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::Input_JumpRelease);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::Input_CrouchPress);
}

void AMainCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AMainCharacter, Rep_Speed, COND_SkipOwner)
	DOREPLIFETIME_CONDITION(AMainCharacter, Rep_AirSpeed, COND_SkipOwner)
	DOREPLIFETIME_CONDITION(AMainCharacter, Rep_Direction, COND_SkipOwner)
	DOREPLIFETIME_CONDITION(AMainCharacter, Rep_Pitch, COND_SkipOwner)
	DOREPLIFETIME_CONDITION(AMainCharacter, Rep_Location, COND_SkipOwner)
	DOREPLIFETIME_CONDITION(AMainCharacter, Rep_Rotation, COND_SkipOwner)
	DOREPLIFETIME_CONDITION(AMainCharacter, Rep_Crouch, COND_SkipOwner)
	DOREPLIFETIME(AMainCharacter, Rep_UseSmooth)
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	Begin_Bind();
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Tick_Calculate(DeltaTime);
	Tick_Update(DeltaTime);
	Tick_Smooth(DeltaTime);
	Tick_Camera(DeltaTime);
	Tick_Crouch(DeltaTime);
}

void AMainCharacter::Input_MoveForward(float Value)
{
	if (Value == 0.0f || !CanMove)
	{
		return;
	}
	FVector dir = UKismetMathLibrary::GetForwardVector(GetActorRotation());
	AddMovementInput(dir, Value);
}

void AMainCharacter::Input_MoveRight(float Value)
{
	if (Value == 0.0f || !CanMove)
	{
		return;
	}
	FVector dir = UKismetMathLibrary::GetRightVector(GetActorRotation());
	AddMovementInput(dir, Value);
}

void AMainCharacter::Input_LookUp(float Value)
{
	if (Value == 0.0f || !CanTurn)
	{
		return;
	}
	AddControllerPitchInput(Value);
}

void AMainCharacter::Input_LookRight(float Value)
{
	if (Value == 0.0f || !CanTurn)
	{
		return;
	}
	AddControllerYawInput(Value);
}

void AMainCharacter::Input_JumpPress()
{
	if (!CanMove)
	{
		return;
	}
	if (Rep_Crouch)
	{
		SetCrouch(false);
		return;
	}
	Jump();
}

void AMainCharacter::Input_JumpRelease()
{
	StopJumping();
}

void AMainCharacter::Input_RunPress()
{
	if (!CanMove)
	{
		return;
	}
	Limit_Speed->RemoveLimit("Jog");
	GetCharacterMovement()->MaxWalkSpeed = Limit_Speed->GetLimit();
}

void AMainCharacter::Input_RunRelease()
{
	Limit_Speed->AddLimit(400.0f, "Jog");
	GetCharacterMovement()->MaxWalkSpeed = Limit_Speed->GetLimit();
}

void AMainCharacter::Input_CrouchPress()
{
	SetCrouch(!Rep_Crouch);
}

void AMainCharacter::Init_Default()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(false);
}

void AMainCharacter::Init_Component()
{
	SkeletalMesh_First = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh_First");
	SkeletalMesh_First->SetupAttachment(RootComponent);

	SkeletalMesh_Third = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh_Third");
	SkeletalMesh_Third->SetupAttachment(RootComponent);

	SpringArm_First = CreateDefaultSubobject<USpringArmComponent>("SpringArm_First");
	SpringArm_First->SetupAttachment(SkeletalMesh_First, "camera_socket");
	SpringArm_First->TargetArmLength = 0.0f;

	Camera_First = CreateDefaultSubobject<UCameraComponent>("Camera_First");
	Camera_First->SetupAttachment(SpringArm_First);

	Limit_Speed = CreateDefaultSubobject<ULimitComponent>("Limit_Speed");
}

void AMainCharacter::Init_Value()
{
	Limit_Speed->LimitList.Add({600.0f, "Run"});
	Limit_Speed->LimitList.Add({400.0f, "Jog"});
}

void AMainCharacter::Begin_Bind()
{
}

void AMainCharacter::Tick_Calculate(float DeltaTime)
{
	if (!IsLocallyControlled())
	{
		return;
	}
	Rep_Speed = GetVelocity().Size2D();
	Rep_AirSpeed = GetVelocity().Z;
	Rep_Direction = Rep_Speed != 0.0f ? SkeletalMesh_First->GetAnimInstance()->CalculateDirection(GetVelocity(), GetActorRotation()) : 0.0f;
	Rep_Pitch = UKismetMathLibrary::NormalizedDeltaRotator(GetControlRotation(), GetActorRotation()).Pitch;
	Rep_Location = GetActorLocation();
	Rep_Rotation = GetActorRotation();
}

void AMainCharacter::Tick_Update(float DeltaTime)
{
	if (!IsLocallyControlled())
	{
		return;
	}
	FUpdateVariable update_var;
	update_var.Speed = Rep_Speed;
	update_var.AirSpeed = Rep_AirSpeed;
	update_var.Direction = Rep_Direction;
	update_var.Pitch = Rep_Pitch;
	update_var.Location = Rep_Location;
	update_var.Rotation = Rep_Rotation;
	update_var.Crouch = Rep_Crouch;
	UpdateVariable_Server(update_var);
}

void AMainCharacter::Tick_Smooth(float DeltaTime)
{
	if (IsLocallyControlled() || !Rep_UseSmooth)
	{
		return;
	}
	float move_alpha = UKismetMathLibrary::FClamp(DeltaTime / GetServerDeltaTime(), 0.0f, 1.0f);
	SetActorLocation(UKismetMathLibrary::VLerp(GetActorLocation(), Rep_Location, move_alpha));
	SetActorRotation(UKismetMathLibrary::RLerp(GetActorRotation(), Rep_Rotation, move_alpha, true));
}

void AMainCharacter::Tick_Camera(float DeltaTime)
{
}

void AMainCharacter::Tick_Crouch(float DeltaTime)
{
}

float AMainCharacter::GetServerDeltaTime()
{
	if (!GameState)
	{
		GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState());
		return 0.0f;
	}
	return GameState->ServerDeltaTime;
}

void AMainCharacter::SetCrouch(bool NewCrouch)
{
	Rep_Crouch = NewCrouch;
	if (Rep_Crouch)
	{
		Limit_Speed->AddLimit(150.0f, "Crouch");
		GetCharacterMovement()->MaxWalkSpeed = Limit_Speed->GetLimit();
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = 60.0f;
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = -60.0f;
	}
	else
	{
		Limit_Speed->RemoveLimit("Crouch");
		GetCharacterMovement()->MaxWalkSpeed = Limit_Speed->GetLimit();
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = 80.0f;
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = -80.0f;
	}
	OnRep_Crouch();
}

void AMainCharacter::OnRep_Crouch()
{
	float height;
	float z_pos;
	if (Rep_Crouch)
	{
		height = 60.0f;
		z_pos = -60.0f;
	}
	else
	{
		height = 90.0f;
		z_pos = -90.0f;
	}
	GetCapsuleComponent()->SetCapsuleHalfHeight(height);
	SkeletalMesh_Third->SetRelativeLocation(FVector(0.0f, 0.0f, z_pos));
	SkeletalMesh_First->SetRelativeLocation(FVector(0.0f, 0.0f, z_pos));
}

FAnimVariable AMainCharacter::GetAnimVariable()
{
	FAnimVariable rtn_value;
	rtn_value.Speed = Rep_Speed;
	rtn_value.AirSpeed = Rep_AirSpeed;
	rtn_value.Direction = Rep_Direction;
	rtn_value.Pitch = Rep_Pitch;
	rtn_value.Crouch = Rep_Crouch;

	return rtn_value;
}

void AMainCharacter::UpdateVariable_Server_Implementation(FUpdateVariable Var)
{
	Rep_Speed = Var.Speed;
	Rep_AirSpeed = Var.AirSpeed;
	Rep_Direction = Var.Direction;
	Rep_Pitch = Var.Pitch;
	Rep_Location = Var.Location;
	Rep_Rotation = Var.Rotation;
	Rep_UseSmooth = true;
	if (Rep_Crouch != Var.Crouch)
	{
		Rep_Crouch = Var.Crouch;
		OnRep_Crouch();
	}
}
