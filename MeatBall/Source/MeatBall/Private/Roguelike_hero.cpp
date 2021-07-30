// Copyright 2021, Aks, Spirt


#include "Roguelike_hero.h"

// Sets default values
ARoguelike_hero::ARoguelike_hero()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);
	GetCharacterMovement()->JumpZVelocity = 700;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 400;
	GetCharacterMovement()->SetWalkableFloorAngle(60);
}

void ARoguelike_hero::MoveForvard(float Axis)
{
	if (Controller != NULL && Axis != 0.0f && !Death)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Axis);
	}
}

void ARoguelike_hero::MoveRight(float Axis)
{
	if (Controller != NULL && Axis != 0.0f && !Death)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Axis);
	}
}

void ARoguelike_hero::Jump()
{
	if (Controller != NULL && !Death)
	{
		ACharacter::Jump();
	}
}

void ARoguelike_hero::DontJump()
{
	if (Controller != NULL && !Death)
	{
		ACharacter::StopJumping();
	}
}

// Called when the game starts or when spawned
void ARoguelike_hero::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARoguelike_hero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARoguelike_hero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARoguelike_hero::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARoguelike_hero::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARoguelike_hero::MoveForvard);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARoguelike_hero::MoveRight);

}

void ARoguelike_hero::App_stat_item(Fcharacteristic_passiv_item char_object, UCharacterMovementComponent* com)
{
	//GetCharacterMovement()->MaxWalkSpeed += char_object.speed;
	//GetCharacterMovement()->JumpZVelocity += char_object.jump_height;

	com->MaxWalkSpeed += char_object.speed;

	//static const UCharacterMovementComponent* com = this.ACharacter::GetCharacterMovement();
}
