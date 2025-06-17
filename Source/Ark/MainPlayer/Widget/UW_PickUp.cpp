#include "UW_PickUp.h"

#include "Ark/MainPlayer/MainCharacter.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

void UUW_PickUp::NativeConstruct()
{
	Super::NativeConstruct();
	const FText in_text = FText::FromString(FString::FromInt(Index + 3));
	TextBlock_Key->SetText(in_text);
}

void UUW_PickUp::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (OwningCharacter)
	{
		const AActor* interact_actor = OwningCharacter->PickUpList[Index];
		float alpha;
		if (interact_actor)
		{
			alpha = 0.6f;
		}
		else
		{
			alpha = 0.0f;
		}
		Image_Icon->SetRenderOpacity(alpha);
	}
}

void UUW_PickUp::SetCharacter(AMainCharacter* Character)
{
	OwningCharacter = Character;
}
