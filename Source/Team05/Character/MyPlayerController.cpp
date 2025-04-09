// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"

AMyPlayerController::AMyPlayerController()
	: InputMappingContext(nullptr),
	  MoveAction(nullptr),
	  JumpAction(nullptr),
	  DirectionAction(nullptr),
	  BaseAttackAction(nullptr),
	  SpecialAttackAction(nullptr),
	  SpecialMoveAction(nullptr),
	  GuardAction(nullptr),
	  EmoteAction(nullptr)
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ���� ���� �Է� ��� ����
	FInputModeGameOnly Mode;
	SetInputMode(Mode);
	bShowMouseCursor = false;

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMyPlayerController::PostNetInit()
{
	Super::PostNetInit();

	// Ŭ���̾�Ʈ Ȯ�� �뵵�� ���� ������ ��ġ
	if (IsLocalPlayerController())
	{
		UNetDriver* NetDriver = GetNetDriver();
		if (IsValid(NetDriver))
		{
			UNetConnection* ServerConnection = NetDriver->ServerConnection;
			// ���� Ŀ�ؼ� Ȯ�� ����
		}
	}
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// Ŭ���̾�Ʈ������ OnPossess�� ȣ����� ����
	// ��� OnRep_Owner()�� ȣ��Ǿ� ������ �ʱ�ȭ
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
