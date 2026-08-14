#include "SuperPlayerController.h"
#include "EnhancedInputSubsystems.h"

ASuperPlayerController::ASuperPlayerController() : InputMappingContext(nullptr),
                                                   MoveAction(nullptr),
                                                   LookAction(nullptr)
{
}

void ASuperPlayerController::BeginPlay()
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
        }
    }
}
