#include "Superman.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "SuperPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

ASuperman::ASuperman()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootCapsule"));
	SetRootComponent(CapsuleComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = false;
	/*SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;*/

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);

	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 500.0f;
	LookSpeed = 30.0f;

	MoveInputVector = FVector2D::ZeroVector;
}

void ASuperman::AccumulateMoveVector(const FInputActionValue& Value)
{
	MoveInputVector += Value.Get<FVector2D>();
}

void ASuperman::AccumulateLookVector(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();

	FRotator DeltaRotator(0.0f, 0.0f, 0.0f);
	if (!FMath::IsNearlyZero(LookInput.X))
	{
		DeltaRotator.Yaw = LookInput.X;
	}
	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		DeltaRotator.Pitch = LookInput.Y;
	}
	SetActorRotation(GetActorRotation() + DeltaRotator);
}

void ASuperman::Move(float DeltaTime)
{
	if (!MoveInputVector.IsNearlyZero())
	{
		FVector LocalDirection(MoveInputVector.X, MoveInputVector.Y, 0.0f);
		LocalDirection = LocalDirection.GetClampedToMaxSize(1.0f);
		AddActorLocalOffset(MoveSpeed * DeltaTime * LocalDirection);

		MoveInputVector = FVector2D::ZeroVector;
	}
}

void ASuperman::Look(float DeltaTime)
{
}

void ASuperman::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASuperman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	
}

void ASuperman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASuperPlayerController* PlayerController = Cast<ASuperPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction,
					                      ETriggerEvent::Triggered,
					                      this,
					                      &ASuperman::AccumulateMoveVector);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction,
					                      ETriggerEvent::Triggered,
					                      this,
					                      &ASuperman::AccumulateLookVector);
			}
		}
	}
}

