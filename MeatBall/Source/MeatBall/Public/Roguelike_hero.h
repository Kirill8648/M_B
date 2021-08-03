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
struct  Fcharacteristic_passiv_item : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
		int speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
		int max_speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
		int jump_height = 0;
};


//USTRUCT(BlueprintType)
//struct  FCharacteristic_pills
//{
//	GENERATED_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
//	int multiplier = 1;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	//int number_repetitions = 0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
//	int jump_height = 0;
//};

//количество esper проходов
//акамулятор из айзека
//множитель от персонажа (для всех и для отдельного типа)
//плохой или хороший множитель 
//собития при хорошей или плохой pill
//Max (как в айзке)
//Все пелюли огдного размара как будто
//Все пилюли плохие или хорошие
//Рандомно плохой или хороший эффект
//Случайная пилялю будет

// Массив сылок на функции для каждого собития героя


//Телепорт пилюля теперотирует через 10 сек в место использования 

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
