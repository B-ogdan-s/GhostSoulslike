
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Player.generated.h"

UCLASS()
class MYFIRSTSOULSLIKEGAME_API ACPP_Player : public ACharacter
{
	GENERATED_BODY()

public:
	ACPP_Player();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* Arm;

protected:
	virtual void BeginPlay() override;

private: 

	float TurnSpeed = 5;
	FVector MoveDirection;

private:
	void ForwardMove(float value);
	void RightMove(float value);
	void Turn(float value);
	void LookUp(float value);

	void CharacterMove(float deltaTime);
	FRotator CharacterRotate(float deltaTime);
};
