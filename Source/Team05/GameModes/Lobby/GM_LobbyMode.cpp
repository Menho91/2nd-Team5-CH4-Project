// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Lobby/GM_LobbyMode.h"

#include "GameModes/Lobby/PS_LobbyPlayer.h"
#include "GameModes/Lobby/GS_LobbyState.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"

AGM_LobbyMode::AGM_LobbyMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGM_LobbyMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// �׽�Ʈ��: ������ �÷��̾�� �ڵ����� Ready ���·� ����
	if (APS_LobbyPlayer* PS = Cast<APS_LobbyPlayer>(NewPlayer->PlayerState))
	{
		PS->SetReady(true);
		UE_LOG(LogTemp, Log, TEXT("Player %s is set to Ready (Test Mode)"), *PS->GetPlayerName());
	}
}

void AGM_LobbyMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void AGM_LobbyMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TryStartBattle();
	UpdateCountdown(DeltaSeconds);
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

	if (ReadyCount >= MinPlayersToStart && ReadyCount == GameState->PlayerArray.Num())
	{
		bStartCountdownStarted = true;
		CountdownRemaining = BattleStartDelay;

		if (AGS_LobbyState* GS = GetGameState<AGS_LobbyState>())
		{
			GS->SetLobbyState(ELobbyState::Countdown);
			GS->SetCountdownTime(CountdownRemaining);
		}

		UE_LOG(LogTemp, Log, TEXT("LobbyMode: Countdown Started (%f seconds)"), BattleStartDelay);
	}
}

void AGM_LobbyMode::UpdateCountdown(float DeltaTime)
{
	if (!bStartCountdownStarted || bMatchStarted) return;

	CountdownRemaining -= DeltaTime;

	if (AGS_LobbyState* GS = GetGameState<AGS_LobbyState>())
	{
		GS->SetCountdownTime(FMath::Max(CountdownRemaining, 0.f));
	}

	if (CountdownRemaining <= 0.0f)
	{
		StartBattle();
	}
}

void AGM_LobbyMode::StartBattle()
{
	bMatchStarted = true;

	if (AGS_LobbyState* GS = GetGameState<AGS_LobbyState>())
	{
		GS->SetLobbyState(ELobbyState::Transitioning);
	}

	EBattleMapType SelectedMap = GetRandomMapEnum();
	const FString MapPath = GetMapPathFromEnum(SelectedMap);
	
	GetWorld()->ServerTravel(MapPath);
}

// ���� �� Enum ������ ���� ��� ��ȯ
FString AGM_LobbyMode::GetMapPathFromEnum(EBattleMapType MapType) const
{
	switch (MapType)
	{
	case EBattleMapType::Battlefield_01:
		return TEXT("TestMap");
	case EBattleMapType::Battlefield_02:
		return TEXT("TestMap");
	default:
		return TEXT("TestMap");
	}
}

// ������ �� Enum ����
EBattleMapType AGM_LobbyMode::GetRandomMapEnum() const
{
	//�� �ø��� ���� �����ؾߵ�
	int32 RandIndex = FMath::RandRange(0, 1);
	return static_cast<EBattleMapType>(RandIndex);
}
