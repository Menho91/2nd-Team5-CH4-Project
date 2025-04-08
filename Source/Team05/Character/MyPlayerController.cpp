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

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
			UE_LOG(LogTemp, Log, TEXT("CheckPoint"));
		}
	}

	// Check if this is a local controller
	if (IsLocalController())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Client] BeginPlay - Local Controller confirmed"));

		// Check if the pawn is already possessed
		APawn* MyPawn = GetPawn();
		if (MyPawn)
		{
			// Try to get the display name of the pawn (character)
			FString PawnName = MyPawn->GetName();
			FString CharacterLabel = MyPawn->GetHumanReadableName();

			UE_LOG(LogTemp, Warning, TEXT("[Client] Possessed Pawn: %s (Label: %s)"), *PawnName, *CharacterLabel);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[Client] No Pawn possessed! Possess() might not have been called on client side"));
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
