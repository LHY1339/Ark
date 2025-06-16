#pragma once

#include "CoreMinimal.h"
#include "Ark/Object/P2PSubsystemObject.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "P2PSubsystem.generated.h"


UCLASS()
class ARK_API UP2PSubsystem : public UGameInstanceSubsystem, public FTickableObjectBase
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

public:
	void Ping(FString TargetIP, int TargetPort);
	void Connect(FString IP, int Port, FString Password);
	void FlushSessionList();

private:
	void TickRecv(float DeltaTime);
	void TickPing(float DeltaTime);
	void TickServer(float DeltaTime);

	bool InitMessageSocket();
	bool InitListenSocket();
	bool SendMessage(FSocket* InSocket, FString Message, FString TargetIP, int TargetPort);

	void HandleMessage(FString RecvString);
	void CmdID(TArray<FString> ParamList, FString RecvString);
	void CmdPing(TArray<FString> ParamList, FString RecvString);
	void CmdSession(TArray<FString> ParamList, FString RecvString);

public:
	FSocket* MessageSocket = nullptr;
	FSocket* ListenSocket = nullptr;

	FSession MySession;
	TArray<FPing> PingList;
	TArray<FSession> SessionList;

	FString ServerIP = "";
	int ServerPort = 0;

private:
	bool Tickable = false;
	
	float TickPingWaitTime = 0.0f;
	float TickServerWaitTime = 0.0f;
};
