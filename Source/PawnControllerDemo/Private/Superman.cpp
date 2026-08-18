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

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);

	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 500.0f;
	LookSpeed = 1.0f;
	RollSpeed = 90.0f;

	MoveInputVector = FVector::ZeroVector;
	RotationInput = FRotator::ZeroRotator;

	MinPitch = -85.0f;
	MaxPitch = 85.0f;

	CurrentPitch = 0.0f;
}

void ASuperman::AccumulateMoveVector(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	MoveInputVector += FVector(Input.X, Input.Y, 0.0f);
}

void ASuperman::AccumulateLookVector(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	RotationInput.Yaw += Input.X;
	RotationInput.Pitch += Input.Y;
}

void ASuperman::AccumulateVerticalVector(const FInputActionValue& Value)
{
	MoveInputVector.Z += Value.Get<float>();
}

void ASuperman::AccumulateRollInput(const FInputActionValue& Value)
{
	RotationInput.Roll += Value.Get<float>();
}

void ASuperman::Move(float DeltaTime)
{
	if (!MoveInputVector.IsNearlyZero())
	{
		const FVector LocalDirection = MoveInputVector.GetClampedToMaxSize(1.0f);

		const FVector WorldDelta = GetActorQuat().RotateVector(LocalDirection) * MoveSpeed * DeltaTime;

		FHitResult Hit;
		AddActorWorldOffset(WorldDelta, true, &Hit);

		if (Hit.bBlockingHit && !Hit.bStartPenetrating)
		{
			const FVector Remaining = WorldDelta * (1.0f - Hit.Time);
			const FVector Slide = FVector::VectorPlaneProject(Remaining, Hit.Normal);
			AddActorWorldOffset(Slide, true);
		}
	}
	MoveInputVector = FVector::ZeroVector;
}

void ASuperman::Look(float DeltaTime)
{
	const FRotator DeltaRotation(0.0f, RotationInput.Yaw * LookSpeed, RotationInput.Roll * RollSpeed * DeltaTime);
	if (!DeltaRotation.IsNearlyZero())
	{
		AddActorLocalRotation(DeltaRotation);
	}

	if (!FMath::IsNearlyZero(RotationInput.Pitch))
	{
		CurrentPitch = FMath::ClampAngle(CurrentPitch + RotationInput.Pitch * LookSpeed, MinPitch, MaxPitch);
		SpringArmComponent->SetRelativeRotation(FRotator(CurrentPitch, 0.0f, 0.0f));
	}
	RotationInput = FRotator::ZeroRotator;
}

void ASuperman::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASuperman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	Look(DeltaTime);
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
			if (PlayerController->MoveVerticalAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveVerticalAction,
					                      ETriggerEvent::Triggered,
					                      this,
					                      &ASuperman::AccumulateVerticalVector);
			}
			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(PlayerController->RollAction,
					                      ETriggerEvent::Triggered,
					                      this,
					                      &ASuperman::AccumulateRollInput);
			}
		}
	}
}

