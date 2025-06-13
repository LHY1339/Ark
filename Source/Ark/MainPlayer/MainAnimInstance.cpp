#include "MainAnimInstance.h"

#include "MainCharacter.h"
#include "Ark/Physical/StepPhysicalMaterial.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	Update_GetVariable(DeltaSeconds);
}

void UMainAnimInstance::Update_GetVariable(float DeltaSeconds)
{
	if (!Character)
	{
		Character = Cast<AMainCharacter>(TryGetPawnOwner());
		return;
	}
	FAnimVariable anim_var = Character->GetAnimVariable();
	Speed = anim_var.Speed;
	AirSpeed = anim_var.AirSpeed;
	Direction = anim_var.Direction;
	Pitch = anim_var.Pitch;
	Crouch = anim_var.Crouch;

	//CameraOffset
	if (Character->IsLocallyControlled())
	{
		FVector rtnV;
		FRotator rtnR;
		Character->SkeletalMesh_First->TransformToBoneSpace(
			"root",
			Character->Camera_First->GetComponentLocation(),
			Character->Camera_First->GetComponentRotation(),
			rtnV,
			rtnR
		);
		CameraOffset = -FVector(rtnV.X, rtnV.Y, 0.0f);
	}

	//AnimSpeed
	AnimSpeed = UKismetMathLibrary::FClamp(Speed / 500.0f, 1.0f, 2.0f);
}

void UMainAnimInstance::AnimNotify_StepLeft()
{
	Step("foot_l");
}

void UMainAnimInstance::AnimNotify_StepRight()
{
	Step("foot_r");
}

void UMainAnimInstance::Step(FName SocketName)
{
	if (!GetOwningComponent()->bOnlyOwnerSee && TryGetPawnOwner()->IsLocallyControlled())
	{
		return;
	}
	if (GetOwningComponent()->bOwnerNoSee && !TryGetPawnOwner()->IsLocallyControlled())
	{
		return;
	}

	const FVector start_pos = GetOwningComponent()->GetSocketLocation(SocketName);
	const FVector end_pos = start_pos - FVector(0.0f, 0.0f, 200.0f);
	const TArray<AActor*> igonre;
	FHitResult out_hit;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		start_pos,
		end_pos,
		TraceTypeQuery1,
		false,
		igonre,
		EDrawDebugTrace::ForDuration,
		out_hit,
		true
	);

	if (out_hit.bBlockingHit)
	{
		UStepPhysicalMaterial* step_mat = Cast<UStepPhysicalMaterial>(out_hit.PhysMaterial);
		if (step_mat)
		{
			const float volume = Speed / 500.0f;
			step_mat->PlayStep(GetWorld(), start_pos, volume);
		}
	}
}
