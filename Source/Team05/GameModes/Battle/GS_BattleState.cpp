// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_BattleState.h"

//debug
#include "Kismet/KismetSystemLibrary.h"

// ������ �޼��� ȣ��
void AGS_BattleState::Multicast_PrintMessage_Implementation(const FString& Msg)
{
	UKismetSystemLibrary::PrintString(
		this,
		Msg,
		true,   // ȭ�鿡 ���
		true,   // �α׿��� ���
		FLinearColor::Yellow,
		10.0f    // ���� �ð�
	);
}
