// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyController.generated.h"

/**
 * 
 */
UCLASS()
class TEAM05_API ALobbyController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void PostNetInit() override;
	virtual void PostInitializeComponents() override;

	// Ŭ���̾�Ʈ �� ����: ���� ���� ���� RPC
	UFUNCTION(Server, Reliable)
	void Server_SendSelectionInfo(const FString& Nickname, const FName& CharacterType);


public:
	// UI Ŭ���� ����(�κ� UI����� �ϱ�)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> LobbyUIClass;
};

