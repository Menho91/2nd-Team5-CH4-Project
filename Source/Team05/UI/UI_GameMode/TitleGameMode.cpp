
#include "TitleGameMode.h"
#include "UI/UI_Controller/TitlePlayerController.h"

ATitleGameMode::ATitleGameMode()
{
    PlayerControllerClass = ATitlePlayerController::StaticClass();
    DefaultPawnClass = nullptr; // UI �����̹Ƿ� Pawn ����
}