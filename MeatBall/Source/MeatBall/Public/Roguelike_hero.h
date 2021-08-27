// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/DataTable.h"

//#include "Pills.h"

#include "Roguelike_hero.generated.h"

USTRUCT(BlueprintType)
struct Fcharacteristic_passiv_item : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	int speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	int max_speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	int jump_height = 0;
};

USTRUCT(BlueprintType)
struct FPills_Characteristic : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	int number_repetitions = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	int number_experimental_repetitions = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	float general_multiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	float speed_multiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	float air_control_multiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	float jump_height_multiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	float Bad_multiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	float Good_multiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	bool all_pill_good;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	bool all_pill_bad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	bool random_pill_bad_or_good;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	bool random_pill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	int only_size;
};

UCLASS()
class MEATBALL_API ARoguelike_hero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARoguelike_hero();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Death;

	void MoveForvard(float Axis);
	void MoveRight(float Axis);
	void Jump();
	void DontJump();


	UFUNCTION(BlueprintCallable)
	static void App_stat_item(Fcharacteristic_passiv_item char_object, UCharacterMovementComponent* com);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<APills> mas_pill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPills_Characteristic pills_characteristic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
