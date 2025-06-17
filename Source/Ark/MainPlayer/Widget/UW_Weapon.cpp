#include "UW_Weapon.h"

#include "Components/TextBlock.h"

void UUW_Weapon::NativeConstruct()
{
	Super::NativeConstruct();
	const FText in_text = FText::FromString(FString::FromInt(Index + 1));
	TextBlock_Key->SetText(in_text);
}

void UUW_Weapon::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUW_Weapon::SetCharacter(AMainCharacter* Character)
{
	OwningCharacter = Character;
}
