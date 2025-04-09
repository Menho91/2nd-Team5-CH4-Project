// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PS_LobbyPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TEAM05_API APS_LobbyPlayer : public APlayerState
{
	GENERATED_BODY()
	
public:
	APS_LobbyPlayer();

	// �غ� ���� Ȯ��
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	bool IsReady() const;

	// �غ� ���� ����
	void SetReady(bool bReady);

	// �г��� ���� �� ��ȯ
	void SetNickname(const FString& InName);
	FString GetNickname() const;

	// ĳ���� Ÿ�� ���� �� ��ȯ
	void SetCharacterType(const FName& InType);
	FName GetCharacterType() const;

protected:
	// Replicated ���� ������ ���� �Լ�
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	// ĳ���� ���� �Ϸ� ����
	UPROPERTY(Replicated)
	bool bIsReady = false;

	// �÷��̾� �г���
	UPROPERTY(Replicated)
	FString Nickname;

	// ������ ĳ���� �̸� �Ǵ� Ÿ��
	UPROPERTY(Replicated)
	FName CharacterType;
};
