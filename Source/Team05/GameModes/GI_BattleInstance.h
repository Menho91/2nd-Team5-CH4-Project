// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_BattleInstance.generated.h"

// ĳ���� ������ ��Ÿ���� ������
UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	//�ϴ� ����Ʈ ���� �߰��ϸ� ��
	Knight UMETA(DisplayName = "Knight"),
	Knight_2 UMETA(DisplayName = "Knight")
};

// �� ���� �÷��̾� ������ ������ ����ü (�г��� + ĳ���� ����)
USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString Nickname;

	UPROPERTY()
	ECharacterType CharacterType;

	FPlayerInfo()
		: Nickname(TEXT("")), CharacterType(ECharacterType::Knight)
	{
	}

	FPlayerInfo(const FString& InNickname, ECharacterType InType)
		: Nickname(InNickname), CharacterType(InType)
	{
	}
};

/**
 * 
 */
UCLASS()
class TEAM05_API UGI_BattleInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// �г��� �ߺ� Ȯ��
	bool IsNicknameTaken(const FString& Nickname) const;

	// �÷��̾� ���� ��� (�г��� + ĳ����)
	void RegisterPlayerInfo(const FString& Nickname, ECharacterType Type);

	// GI_BattleInstance.h
	void UpdateCharacterType(const FString& Nickname, ECharacterType NewType);

	// �г������� ĳ���� ���� ��ȸ
	ECharacterType GetCharacterTypeByNickname(const FString& Nickname) const;

private:
	// �г����� Ű�� �� �÷��̾� ���� ��
	UPROPERTY()
	TMap<FString, FPlayerInfo> PlayerInfoMap;
};
