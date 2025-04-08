// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Lobby/PS_LobbyPlayer.h"

#include "Net/UnrealNetwork.h"

APS_LobbyPlayer::APS_LobbyPlayer()
{
	bReplicates = true; // ��Ʈ��ũ ����ȭ ����
}

bool APS_LobbyPlayer::IsReady() const
{
	return bIsReady;
}

void APS_LobbyPlayer::SetReady(bool bReady)
{
	bIsReady = bReady;
}

void APS_LobbyPlayer::SetNickname(const FString& InName)
{
	Nickname = InName;
}

FString APS_LobbyPlayer::GetNickname() const
{
	return Nickname;
}

void APS_LobbyPlayer::SetCharacterType(const FName& InType)
{
	CharacterType = InType;
}

FName APS_LobbyPlayer::GetCharacterType() const
{
	return CharacterType;
}

void APS_LobbyPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicated ó���� ������ ���
	DOREPLIFETIME(APS_LobbyPlayer, bIsReady);
	DOREPLIFETIME(APS_LobbyPlayer, Nickname);
	DOREPLIFETIME(APS_LobbyPlayer, CharacterType);
}

