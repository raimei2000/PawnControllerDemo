#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Superman.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class FInputActionValues;

UCLASS()
class PAWNCONTROLLERDEMO_API ASuperman : public APawn
{
	GENERATED_BODY()

public:
	ASuperman();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Superman|Components")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Superman|Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Superman|Components")
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Superman|Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	/*UFUNCTION()
	void Move(const FInputActionValues& Value);
	UFUNCTION()
	void Look(const FInputActionValues& Value);*/

	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
