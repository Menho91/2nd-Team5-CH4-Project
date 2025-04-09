
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoadingPlayerController.generated.h"

UCLASS()
class TEAM05_API ALoadingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ALoadingPlayerController, Meta = (AllowPrivateAccess))
	TSubclassOf<UUserWidget> UIWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ALoadingPlayerController, Meta = (AllowPrivateAccess))
	TObjectPtr<UUserWidget> UIWidgetInstance;

	// �ڵ� ���� ��ȯ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ALoadingPlayerController, Meta = (AllowPrivateAccess))
	FName NextLevelName = TEXT("_MarioMap");  // ���� ���� �̸�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ALoadingPlayerController, Meta = (AllowPrivateAccess))
	float DelayBeforeTravel = 3.0f;  // ��ȯ���� ��� �ð� (��)

	FTimerHandle TransitionTimerHandle;

	void GoToNextLevel();
};
