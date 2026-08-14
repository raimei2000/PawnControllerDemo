#include "SupermanGameMode.h"

#include "Superman.h"
#include "SuperPlayerController.h"

ASupermanGameMode::ASupermanGameMode()
{
    DefaultPawnClass = ASuperman::StaticClass();
    PlayerControllerClass = ASuperPlayerController::StaticClass();
}
