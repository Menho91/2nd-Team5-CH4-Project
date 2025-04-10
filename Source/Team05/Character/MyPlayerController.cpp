// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ScriptMacros.h"
#include "UObject/UnrealType.h"
#include "GameModes/GI_BattleInstance.h"

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
	/*FInputModeGameOnly Mode;
	SetInputMode(Mode);
	bShowMouseCursor = false;*/

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

	// Ŭ���̾�Ʈ������ ���� UI
	if (IsLocalController())
	{
		if (NameInputUIClass)
		{
			NameInputUI = CreateWidget<UUserWidget>(this, NameInputUIClass);

			if (NameInputUI)
			{
				NameInputUI->AddToViewport();

				// �Է� ��� ����: UIOnly�� ��ȯ + ���콺 Ŀ�� ǥ��
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(NameInputUI->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

				SetInputMode(InputMode);
				bShowMouseCursor = true;

				UE_LOG(LogTemp, Log, TEXT("NameInput UI created and shown."));
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

void AMyPlayerController::Server_CheckNickname_Implementation(const FString& Nickname)
{
	if (UGI_BattleInstance* GI = Cast<UGI_BattleInstance>(GetGameInstance()))
	{
		const bool bAvailable = !GI->IsNicknameTaken(Nickname);

		//�г��� ��� �����ϸ� ���
		if (bAvailable)
		{
			// ĳ���� ���� ������ �ִٸ� �Բ� ��� (��: PlayerState���� ��������)
			ECharacterType SelectedType = ECharacterType::Knight; // �⺻ ĳ����
			GI->RegisterPlayerInfo(Nickname, SelectedType);
		}

		Client_NicknameCheckResult(bAvailable); // ��� ����
	}
}

void AMyPlayerController::Client_NicknameCheckResult_Implementation(bool bAvailable)
{
	if (NameInputUI)
	{
		FName FunctionName = "UpdateWarningText";

		if (NameInputUI->FindFunction(FunctionName))
		{
			struct FNicknameParam { bool bAvailable; };
			FNicknameParam Param{ bAvailable };

			NameInputUI->ProcessEvent(NameInputUI->FindFunction(FunctionName), &Param);
		}
	}
}
