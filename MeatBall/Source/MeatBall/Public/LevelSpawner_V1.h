// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//#include "Kismet/GameplayStatics.h"

#include "Engine/LevelStreamingDynamic.h"
#include "vector"
#include "GameInstanceToSave.h"
#include "RoomBase.h"
#include "Room1Cell.h"
#include "Room2Cells.h"
#include "Room4Cells.h"
#include "LevelSpawner_V1.generated.h"

UCLASS()
class MEATBALL_API ALevelSpawner_V1 : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere) int NumberOf1CellRooms;
	UPROPERTY(EditAnywhere) int NumberOf2CellRooms;
	UPROPERTY(EditAnywhere) int NumberOf4CellRooms;
	UPROPERTY(EditAnywhere) int NumberOfBeginRooms;
	UPROPERTY(EditAnywhere) int NumberOfEndRooms;
	UPROPERTY(EditAnywhere) int LevelsGridSize;
	UPROPERTY(EditAnywhere) int MatrixVerticalSize;
	UPROPERTY(EditAnywhere) int MatrixHorizontalSize;
	std::vector<std::vector<int>> matrix;

	// Sets default values for this actor's properties
	ALevelSpawner_V1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DrawRoomCreationMassage(bool, FString);
	void SpawnRoom(UWorld* world, FString RoomName, FVector RoomVector, FRotator RoomRotator, int UniqueIndex);
	void RecursivePath(int, int, int, int, UWorld*);
};
