// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GS_LobbyState.generated.h"

// �κ��� ���¸� �����ϴ� Enum
UENUM(BlueprintType)
enum class ELobbyState : uint8
{
	Waiting,
	Countdown,
	Transitioning
};

/**
 * 
 */
UCLASS()
class TEAM05_API AGS_LobbyState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AGS_LobbyState();

	// ���� ī��Ʈ�ٿ� �ð� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	float GetCountdownTime() const { return CountdownTime; }

	// �κ� ���� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	ELobbyState GetLobbyState() const { return LobbyState; }

	// �κ� ���� ����
	void SetLobbyState(ELobbyState NewState);
	void SetCountdownTime(float Time);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	// ���� ���۱��� ���� �ð� (Ŭ���̾�Ʈ UI ǥ�ÿ�)
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Lobby", meta = (AllowPrivateAccess = "true"))
	float CountdownTime;

	// �κ��� ���� ����
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Lobby", meta = (AllowPrivateAccess = "true"))
	ELobbyState LobbyState;
};

