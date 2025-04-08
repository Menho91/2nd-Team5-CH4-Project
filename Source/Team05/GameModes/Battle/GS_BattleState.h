// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GS_BattleState.generated.h"

/**
 * 
 */
UCLASS()
class TEAM05_API AGS_BattleState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// ������ ��� Ŭ���̾�Ʈ�� �޽����� ���� �Լ�
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PrintMessage(const FString& Msg);
};
