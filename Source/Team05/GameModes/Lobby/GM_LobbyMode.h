// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GS_LobbyState.h"
#include "GM_LobbyMode.generated.h"

// ���� �� ������ Enum���� ����(�� �߰��ϸ��)
UENUM(BlueprintType)
enum class EBattleMap : uint8
{
	Battlefield_01 UMETA(DisplayName = "_MarioMap"),
	Battlefield_02 UMETA(DisplayName = "_MarioMap")
};

/**
 * 
 */
UCLASS()
class TEAM05_API AGM_LobbyMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGM_LobbyMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	// ���� ���� ���� Ȯ��
	void TryStartBattle();

	// ī��Ʈ�ٿ� ó�� (Ÿ�̸� ���)
	void CountdownTick();

	// ��� ���� ���� ���� Ȯ��
	void CheckReadyToStart();

	// ���� ���� ������ �̵�
	void StartBattle();

	// �� Enum�� �� ��η� ��ȯ
	FString GetBattleMapPath(EBattleMap Map) const;

private:
	// ���� ���� Ȯ��
	FTimerHandle CheckReadyTimerHandle;
	// ī��Ʈ�ٿ� ����
	FTimerHandle CountdownTimerHandle;

	// �غ� �ο� Ȯ�� �� ���� ���۱��� ����ϴ� �ð�
	UPROPERTY(EditDefaultsOnly)
	float BattleStartDelay = 10.0f;

	// �ּ� ���� �ο� ��
	UPROPERTY(EditDefaultsOnly)
	int32 MinPlayersToStart = 2;

	// ���� ����
	bool bStartCountdownStarted;
	bool bMatchStarted;
	float CountdownRemaining;
};

