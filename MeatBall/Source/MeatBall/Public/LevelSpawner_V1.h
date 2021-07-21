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

		// Sets default values for this actor's properties
		ALevelSpawner_V1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	struct Vector
	{
		int x;
		int y;
	};
	UPROPERTY(EditAnywhere) int NumberOf1CellRooms;
	UPROPERTY(EditAnywhere) int NumberOf2CellRooms;
	UPROPERTY(EditAnywhere) int NumberOf4CellRooms;
	UPROPERTY(EditAnywhere) int NumberOfBeginRooms;
	UPROPERTY(EditAnywhere) int NumberOfEndRooms;
	UPROPERTY(EditAnywhere) int LevelsGridSize;
	UPROPERTY(EditAnywhere) int MatrixVerticalSize;
	UPROPERTY(EditAnywhere) int MatrixHorizontalSize;
	UPROPERTY(EditAnywhere) int NumberOfRoomsToSpawn;

	int CounterToSpawn = 500;
	std::vector<std::vector<int>> matrix;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//void DrawRoomCreationMassage(bool, FString);
	void SpawnRoom(UWorld*, FString, FVector, FRotator, int);
	void RecursivePath(int, int, int, int, UWorld*);
	static void PrintMap(std::vector<std::vector<int>>& mas);

	static int obr_point_int(std::vector<std::vector<int>>& mas, int x, int y);
	static int procedure_gen_mega_rand_with_rand_room_int(std::vector<std::vector<int>>& mas, int number_rooms);
	static void Generation_Map_Test1_int(std::vector<std::vector<int>>& mas, int number_rooms);
	static int fun_long_room_int(std::vector<std::vector<int>>& mas, int lenght_room, int x, int y);
	static int fun_fin_long_room_int(std::vector<std::vector<int>>& mas, int lenght_room, int x, int y, int vec_x, int vex_y);
	static int change_data_int(std::vector<std::vector<int>>& mas, int lenght_room, int& x, int& y, int vec_x, int vec_y);
	static void delete_walls(std::vector<std::vector<int>>& mas);

};
