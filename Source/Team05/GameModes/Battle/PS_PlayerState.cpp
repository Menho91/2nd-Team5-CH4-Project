// Fill out your copyright notice in the Description page of Project Settings.


#include "PS_PlayerState.h"

#include "Net/UnrealNetwork.h"

APS_PlayerState::APS_PlayerState()
{
	// �⺻ ĳ���ʹ� Knight�� ����
	CharacterType = ECharacterType::Knight;
}

void APS_PlayerState::SetCharacterType(ECharacterType InType)
{
	CharacterType = InType;
}

ECharacterType APS_PlayerState::GetCharacterType() const
{
	return CharacterType;
}

void APS_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APS_PlayerState, CharacterType);
}


