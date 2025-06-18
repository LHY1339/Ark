#include "UW_Interact.h"

#include "Ark/Interface/IInteract.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUW_Interact::NativeConstruct()
{
	Super::NativeConstruct();
	if (InteractActor && OwningCharacter)
	{
		FPickUpProperty prop = IIInteract::Execute_GetPickUpProperty(InteractActor, OwningCharacter);
		Image_Texture->SetBrushResourceObject(prop.Texture);
		Image_BK->SetColorAndOpacity(prop.BackColor);
		TextBlock_Name->SetText(FText::FromString(prop.Name));
		TextBlock_Description->SetText(FText::FromString(prop.Description));
		TextBlock_Name->SetColorAndOpacity(FSlateColor(prop.NameColor));
		TextBlock_Description->SetColorAndOpacity(FSlateColor(prop.DescriptionColor));
	}
}

void UUW_Interact::SetCharacter(AMainCharacter* Character)
{
	OwningCharacter = Character;
}
