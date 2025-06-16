#pragma once

#include "CoreMinimal.h"
#include "P2PSubsystemObject.generated.h"


USTRUCT(BlueprintType)
struct FSession
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString IP = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Port = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ID = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name = "NULL";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Level = "NULL";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PlayerNum = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Password = "";

	bool operator==(const FSession& Other);
};

USTRUCT()
struct FPing
{
	GENERATED_BODY()

	UPROPERTY()
	FString IP;

	UPROPERTY()
	int Port;

	UPROPERTY()
	FString Password = "";

	UPROPERTY()
	int Times = 2;
};

UCLASS()
class ARK_API UP2PLibrary : public UObject
{
	GENERATED_BODY()

public:
	static TArray<FString> BreakString(FString BaseStr, FString Breaker);
};
