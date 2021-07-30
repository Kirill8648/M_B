// Copyright 2021, Aks, Spirt


#include "Passive_item.h"

// Sets default values
APassive_item::APassive_item()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	characteristic_passiv_item.speed = 0;
	characteristic_passiv_item.max_speed = 0;
	characteristic_passiv_item.jump_height = 0;
}

// Called when the game starts or when spawned
void APassive_item::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APassive_item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

