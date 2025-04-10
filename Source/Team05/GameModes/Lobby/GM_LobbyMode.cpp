// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Lobby/GM_LobbyMode.h"

#include "GameModes/Lobby/PS_LobbyPlayer.h"
#include "GameModes/Lobby/GS_LobbyState.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"

AGM_LobbyMode::AGM_LobbyMode()
{
	PrimaryActorTick.bCanEverTick = false;

	// �ʱ� ���°� ����
	BattleStartDelay = 10.0f;
	MinPlayersToStart = 2;
	bStartCountdownStarted = false;
	bMatchStarted = false;
	CountdownRemaining = 0.0f;
}

void AGM_LobbyMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// 1�� �������� ���� ���� üũ
	GetWorldTimerManager().SetTimer(CheckReadyTimerHandle, this, &AGM_LobbyMode::CheckReadyToStart, 1.0f, true);
}

void AGM_LobbyMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void AGM_LobbyMode::TryStartBattle()
{
	if (bMatchStarted || bStartCountdownStarted) return;

	int32 ReadyCount = 0;

	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (const APS_LobbyPlayer* MyPS = Cast<APS_LobbyPlayer>(PS))
		{
			if (MyPS->IsReady())
			{
				ReadyCount++;
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("LobbyMode: ReadyCount = %d / Total = %d"), ReadyCount, GameState->PlayerArray.Num());

	// ��� �÷��̾ Ready ���¸� ī��Ʈ�ٿ� ����
	if (ReadyCount >= MinPlayersToStart && ReadyCount == GameState->PlayerArray.Num())
	{
		bStartCountdownStarted = true;
		CountdownRemaining = BattleStartDelay;

		if (AGS_LobbyState* GS = GetGameState<AGS_LobbyState>())
		{
			GS->SetLobbyState(ELobbyState::Countdown);
			GS->SetCountdownTime(CountdownRemaining);
		}

		// Ÿ�̸� ���� (1�� ����)
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AGM_LobbyMode::CountdownTick, 1.0f, true);

		UE_LOG(LogTemp, Log, TEXT("LobbyMode: Countdown Started (%f seconds)"), BattleStartDelay);
	}
}

void AGM_LobbyMode::CountdownTick()
{
	CountdownRemaining -= 1.0f;

	if (AGS_LobbyState* GS = GetGameState<AGS_LobbyState>())
	{
		GS->SetCountdownTime(FMath::Max(CountdownRemaining, 0.0f));
	}

	if (CountdownRemaining <= 0.0f)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		StartBattle();
	}
}

void AGM_LobbyMode::CheckReadyToStart()
{
	if (!bMatchStarted && !bStartCountdownStarted)
	{
		TryStartBattle();
	}
}

void AGM_LobbyMode::StartBattle()
{
	bMatchStarted = true;

	UE_LOG(LogTemp, Log, TEXT("LobbyMode: Starting Battle..."));

	// ���� �� ����
	int32 MapIndex = FMath::RandRange(0, 1);  // Enum �� ���� �� �þ�� ���� (0~1)
	EBattleMap SelectedMap = static_cast<EBattleMap>(MapIndex);
	FString MapPath = GetBattleMapPath(SelectedMap);

	UE_LOG(LogTemp, Log, TEXT("LobbyMode: Selected Map = %s"), *MapPath);

	// ���� ������ ��ȯ
	GetWorld()->ServerTravel(MapPath);
}

FString AGM_LobbyMode::GetBattleMapPath(EBattleMap Map) const
{
	switch (Map)
	{
	case EBattleMap::Battlefield_01:
		return TEXT("_MarioMap");
	case EBattleMap::Battlefield_02:
		return TEXT("_MarioMap");
	default:
		return TEXT("_MarioMap");
	}
}