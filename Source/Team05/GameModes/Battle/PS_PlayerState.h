// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PS_PlayerState.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Knight UMETA(DisplayName = "Knight")
	// ĳ�� �߰��ϸ� Ȯ��
};

/**
 * 
 */
UCLASS()
class TEAM05_API APS_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	APS_PlayerState();

	void SetCharacterType(ECharacterType InType);
	ECharacterType GetCharacterType() const;

protected:
	// ���õ� ĳ���� ����
	UPROPERTY(Replicated)
	ECharacterType CharacterType;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
