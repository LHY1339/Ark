#include "UW_MainPlayer.h"

#include <filesystem>

#include "UW_Interact.h"
#include "UW_PickUp.h"
#include "UW_Weapon.h"
#include "Components/ScrollBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/Text/ISlateEditableTextWidget.h"

void UUW_MainPlayer::AddActorToInteractList(AActor* NewActor)
{
	UUW_Interact* interact_inst = CreateWidget<UUW_Interact>(GetWorld(), InteractWidgetClass);
	if (interact_inst)
	{
		interact_inst->InteractActor = NewActor;
		interact_inst->SetCharacter(OwningCharacter);
		ScrollBox_Interact->AddChild(interact_inst);
	}
}

void UUW_MainPlayer::RemoveActorFromInteractList(AActor* Actor)
{
	for (int i = 0; i < ScrollBox_Interact->GetChildrenCount(); i++)
	{
		UWidget* cur_widget = ScrollBox_Interact->GetAllChildren()[i];
		UUW_Interact* cur_interact_widget = Cast<UUW_Interact>(cur_widget);
		if (cur_interact_widget && cur_interact_widget->InteractActor == Actor)
		{
			ScrollBox_Interact->RemoveChildAt(i);
			return;
		}
	}
}

void UUW_MainPlayer::FlushInteractList()
{
}

void UUW_MainPlayer::SetCharacter(AMainCharacter* Character)
{
	OwningCharacter = Character;
	UMG_PickUp_1->SetCharacter(Character);
	UMG_PickUp_2->SetCharacter(Character);
	UMG_PickUp_3->SetCharacter(Character);
	UMG_PickUp_4->SetCharacter(Character);
	UMG_PickUp_5->SetCharacter(Character);
	UMG_Weapon_1->SetCharacter(Character);
	UMG_Weapon_2->SetCharacter(Character);
}
