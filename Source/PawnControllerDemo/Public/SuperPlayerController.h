#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SuperPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PAWNCONTROLLERDEMO_API ASuperPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASuperPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

protected:
	virtual void BeginPlay() override;
};
