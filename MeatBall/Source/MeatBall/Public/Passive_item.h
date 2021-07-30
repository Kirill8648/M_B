// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Roguelike_hero.h"

#include "Passive_item.generated.h"

UCLASS()
class MEATBALL_API APassive_item : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APassive_item();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		Fcharacteristic_passiv_item characteristic_passiv_item;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
