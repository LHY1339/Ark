#include "UW_MainPlayer.h"
#include "UW_Interact.h"
#include "Components/ScrollBox.h"
#include "Kismet/KismetSystemLibrary.h"

void UUW_MainPlayer::AddActorToInteractList(AActor* NewActor)
{
	//UKismetSystemLibrary::PrintString(GetWorld(), NewActor->GetName());
	UUW_Interact* interact_inst = CreateWidget<UUW_Interact>(GetWorld(), InteractWidgetClass);
	if (interact_inst)
	{
		interact_inst->InteractActor = NewActor;
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
