// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GS_LobbyState.generated.h"

// �κ� ���¸� ǥ���ϴ� Enum
UENUM(BlueprintType)
enum class ELobbyState : uint8
{
	Waiting UMETA(DisplayName = "Waiting"),
	Countdown UMETA(DisplayName = "Countdown"),
	Started UMETA(DisplayName = "Started")
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

	// ���� ���� �Լ�
	void SetLobbyState(ELobbyState NewState);
	ELobbyState GetLobbyState() const;

	// ī��Ʈ�ٿ� ����
	void SetCountdownTime(float NewTime);
	float GetCountdownTime() const;

protected:
	// ���� ��� ���
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	// �κ� ���� ����
	UPROPERTY(Replicated)
	ELobbyState LobbyState;

	// ���� ���۱��� ���� �ð�
	UPROPERTY(Replicated)
	float CountdownTime;
};

