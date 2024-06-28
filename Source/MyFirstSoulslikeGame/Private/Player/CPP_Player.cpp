
#include "Player/CPP_Player.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/SpringArmComponent.h"

ACPP_Player::ACPP_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->SetupAttachment(GetRootComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->AttachToComponent(Arm, FAttachmentTransformRules::KeepRelativeTransform);
	//CharacterTrajectory = CreateDefaultSubobject<UCharacterTrajectoryComponent>(TEXT("CharacterTrajectory"));

	Arm->bUsePawnControlRotation = true;
	Arm->bEnableCameraLag = true;
}

void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CharacterMove(DeltaTime);
}

void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardMove", this, &ACPP_Player::ForwardMove);
	PlayerInputComponent->BindAxis("RightMove", this, &ACPP_Player::RightMove);
	PlayerInputComponent->BindAxis("Turn", this, &ACPP_Player::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPP_Player::LookUp);
}


void ACPP_Player::ForwardMove(float value)
{
	MoveDirection.X = value;
}
void ACPP_Player::RightMove(float value)
{
	MoveDirection.Y = value;
}

void ACPP_Player::Turn(float value)
{
	AddControllerYawInput(value);
}
void ACPP_Player::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void ACPP_Player::CharacterMove(float deltaTime)
{
	if (MoveDirection.SizeSquared() == 0)
		return;

    FRotator Rot = CharacterRotate(deltaTime);

	FVector Direction = FRotationMatrix(Rot).GetUnitAxis(EAxis::X) * MoveDirection.X + FRotationMatrix(Rot).GetUnitAxis(EAxis::Y) * MoveDirection.Y;

	if (Direction.SizeSquared() > 1)
	{
		Direction.Normalize();
	}

	AddMovementInput(Direction, 1.0f);
}

FRotator ACPP_Player::CharacterRotate(float deltaTime)
{
	FRotator Rotation = GetActorRotation();
	FRotator Rot = FRotator::ZeroRotator;
	Rot.Yaw = Camera->GetComponentRotation().Yaw;

	Rotation = FMath::RInterpTo(Rotation, Rot + MoveDirection.Rotation(), deltaTime, TurnSpeed);
	SetActorRotation(Rotation);

	return Rot;
}

