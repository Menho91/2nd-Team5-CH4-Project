#include "LoadingPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widgets/LoadingLayout.h"
#include "Kismet/GameplayStatics.h"

void ALoadingPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (true == ::IsValid(UIWidgetClass))
	{
		UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
		if (true == ::IsValid(UIWidgetInstance))
		{
			UIWidgetInstance->AddToViewport();

			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
			SetInputMode(Mode);

			bShowMouseCursor = false;  // �ε� ȭ�鿡���� Ŀ�� ��Ȱ��ȭ
		}
	}

	// ���� �ð� �� �ڵ����� ���� �̵�
	GetWorldTimerManager().SetTimer(
		TransitionTimerHandle,
		this,
		&ALoadingPlayerController::GoToNextLevel,
		DelayBeforeTravel,
		false
	);
}

void ALoadingPlayerController::GoToNextLevel()
{
	UGameplayStatics::OpenLevel(this, NextLevelName);
}