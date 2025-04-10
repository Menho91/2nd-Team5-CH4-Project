// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameModes/GI_BattleInstance.h"
#include "InformationChck.generated.h"

/**
 * 
 */
UCLASS()
class TEAM05_API UInformationChck : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	// �г����� ��� �������� �������� Ȯ��
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "PlayerInfo")
	void Server_CheckNickname(UObject* WorldContextObject, const FString& Nickname);

	// �г��� ��� ��û
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "PlayerInfo")
	void Server_RegisterNickname(UObject* WorldContextObject, const FString& Nickname);

	// ĳ���� Ÿ�� ��� ��û
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "PlayerInfo")
	void Server_RegisterCharacterType(UObject* WorldContextObject, const FString& Nickname, ECharacterType CharacterType);

	// ĳ���� Ÿ�� ��ȸ�� Ŭ�󿡼��� ���� (�б� �����̶��)
	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	ECharacterType GetCharacterTypeByNickname(UObject* WorldContextObject, const FString& Nickname);

};
