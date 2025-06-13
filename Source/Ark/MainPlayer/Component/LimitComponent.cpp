#include "LimitComponent.h"

void ULimitComponent::AddLimit(float NewValue, FString NewName)
{
	for (FFloatLimit& limit : LimitList)
	{
		if (limit.Name == NewName)
		{
			limit.Value = NewValue;
			return;
		}
	}
	FFloatLimit new_limit;
	new_limit.Value = NewValue;
	new_limit.Name = NewName;
	LimitList.Add(new_limit);
}

void ULimitComponent::RemoveLimit(FString NewName)
{
	for (int i = 0; i < LimitList.Num(); i++)
	{
		if (LimitList[i].Name == NewName)
		{
			LimitList.RemoveAt(i);
			return;
		}
	}
}

bool ULimitComponent::IsLimitValid(FString NewName)
{
	for (FFloatLimit& limit : LimitList)
	{
		if (limit.Name == NewName)
		{
			return true;
		}
	}
	return false;
}

float ULimitComponent::GetLimit(FString NewName)
{
	for (FFloatLimit& limit : LimitList)
	{
		if (limit.Name == NewName)
		{
			return limit.Value;
		}
	}
	return 0.0f;
}

float ULimitComponent::GetLimit()
{
	if (LimitList.Num() <= 0)
	{
		return 0.0f;
	}
	float min_value = LimitList[0].Value;
	for (FFloatLimit& limit : LimitList)
	{
		if (limit.Value < min_value)
		{
			min_value = limit.Value;
		}
	}
	return min_value;
}
