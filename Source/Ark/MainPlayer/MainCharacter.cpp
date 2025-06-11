#include "MainCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMainCharacter::AMainCharacter()
{
	Init_Default();
	Init_Component();
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMainCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AMainCharacter::Init_Default()
{
	PrimaryActorTick.bCanEverTick = true;
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
}
