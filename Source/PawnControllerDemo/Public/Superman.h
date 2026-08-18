#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Superman.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Superman|Input")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Superman|Input")
	float LookSpeed;

	FVector MoveInputVector;
	FVector2D LookInputVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Superman|Input")
	float MinPitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Superman|Input")
	float MaxPitch;

protected:
	UFUNCTION()
	void AccumulateMoveVector(const FInputActionValue& Value);
	UFUNCTION()
	void AccumulateLookVector(const FInputActionValue& Value);
	UFUNCTION()
	void AccumulateVerticalVector(const FInputActionValue& Value);

	void Move(float DeltaTime);
	void Look();

	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float CurrentPitch;

};
