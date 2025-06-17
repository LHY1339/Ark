#include "MainPickUp.h"

#include "Ark/MainPlayer/MainCharacter.h"
#include "Ark/MainPlayer/Widget/UW_MainPlayer.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

AMainPickUp::AMainPickUp()
{
	Init_Default();
	Init_Component();
}

void AMainPickUp::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainPickUp, CanInteract)
}

void AMainPickUp::Interact_Implementation(AMainCharacter* Character)
{
	int index;
	if (PickUpCond(Character, index))
	{
		PickUp(Character, index);
	}
}

bool AMainPickUp::GetCanInteract_Implementation(AMainCharacter* Character)
{
	return CanInteract;
}

void AMainPickUp::SetWidgetCharacter_Implementation(AMainCharacter* Character)
{
	WidgetCharacter = Character;
}

FPickUpProperty AMainPickUp::GetPickUpProperty_Implementation(AMainCharacter* Character)
{
	FPickUpProperty pick_up_prop;
	pick_up_prop.Texture = Texture;
	pick_up_prop.Name = Name;
	pick_up_prop.Description = Description;
	pick_up_prop.BackColor = BackColor;
	pick_up_prop.TextColor = TextColor;
	return pick_up_prop;
}

void AMainPickUp::Init_Default()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);
}

void AMainPickUp::Init_Component()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Box_Collision = CreateDefaultSubobject<UBoxComponent>("Box_Collision");
	Box_Collision->SetupAttachment(RootComponent);

	Scene_AttachFirst = CreateDefaultSubobject<USceneComponent>(FName("Scene_AttachFirst"));
	Scene_AttachFirst->SetupAttachment(RootComponent);

	Scene_AttachThird = CreateDefaultSubobject<USceneComponent>(FName("Scene_AttachThird"));
	Scene_AttachThird->SetupAttachment(RootComponent);
}

bool AMainPickUp::PickUpCond(AMainCharacter* Character, int& Num)
{
	if (!CanInteract)
	{
		return false;
	}
	for (int i = 0; i < Character->PickUpList.Num(); i++)
	{
		const AActor* cur_pickup = Character->PickUpList[i];
		if (cur_pickup == nullptr)
		{
			Num = i;
			return true;
		}
	}
	return false;
}

void AMainPickUp::PickUp(AMainCharacter* Character, int Num)
{
	SetCanInteract(false);
	SetOwner(Character);
	Character->PickUpList[Num] = this;

	AttachToActor(Character, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	Scene_AttachFirst->AttachToComponent(
		Character->SkeletalMesh_First,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		"pickup_socket"
	);

	Scene_AttachThird->AttachToComponent(
		Character->SkeletalMesh_Third,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		"pickup_socket"
	);
}

bool AMainPickUp::DropCond(AMainCharacter* Character, int& Num)
{
	for (int i = 0; i < Character->PickUpList.Num(); i++)
	{
		const AActor* cur_pickup = Character->PickUpList[i];
		if (cur_pickup == this)
		{
			Num = i;
			return true;
		}
	}
	return false;
}

void AMainPickUp::Drop(AMainCharacter* Character, int Num)
{
	Scene_AttachFirst->AttachToComponent(
		RootComponent,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale
	);

	Scene_AttachThird->AttachToComponent(
		RootComponent,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale
	);

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	Character->PickUpList[Num] = nullptr;
	SetOwner(nullptr);
	SetCanInteract(true);
}

void AMainPickUp::OnRep_CanInteract()
{
	if (!WidgetCharacter || !WidgetCharacter->MainPlayerWidget)
	{
		return;
	}
	if (CanInteract)
	{
		WidgetCharacter->MainPlayerWidget->AddActorToInteractList(this);
	}
	else
	{
		WidgetCharacter->MainPlayerWidget->RemoveActorFromInteractList(this);
	}
}

void AMainPickUp::SetCanInteract(bool NewCanInteract)
{
	CanInteract = NewCanInteract;
	OnRep_CanInteract();
}
