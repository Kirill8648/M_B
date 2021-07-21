// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "vector"
#include "string"
#include "Engine/DataTable.h"
#include "Engine/LevelStreamingDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "LevelSpawner3D_V1.generated.h"

USTRUCT(BlueprintType)
struct FRoomDataStruct : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString RoomNameToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FVector> VectorsToFill;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FVector> AdditionalVectorsToCheck;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector CoordsNearExit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector CoordsBehindExit;
};

UCLASS()
class MEATBALL_API ALevelSpawner3D_V1 : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrix")
	int LevelsGridSizeXY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrix")
	int LevelsGridSizeZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sizes")
	int MatrixZSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sizes")
	int MatrixXSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sizes")
	int MatrixYSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sizes")
	int MatrixBorderSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay Shit")
	int NumberOfRoomsToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	UDataTable* RoomsDataTable;

	struct FRoomDataToSpawnStruct
	{
		FString SpawnName;
		std::string SpawnNameStd;
		FVector SpawnVector;
		FRotator SpawnRotator;
	};

	struct FCoord
	{
		int X;
		int Y;
		int Z;
	};

	// Sets default values for this actor's properties
	ALevelSpawner3D_V1();

	void SetMatrix();
	void PrintMatrixToLog();
	void SpawnRoom(UWorld* World, FString RoomName, FVector RoomVector, FRotator RoomRotator);
	int ProcedurallyGenerateSetOfRooms(UWorld* World);
	void SpawnSetOfRooms(UWorld* World/*, TArray<FRoomDataToSpawnStruct*> TempRoomsToSpawnSet*/);
	static FVector RotateFVectorAroundZ(FVector InputVector, int Angle);
	static FCoord RotateFCoordAroundZ(FCoord InputCoord, int Angle);
	static int CalculateAngleByCoords(FCoord PrevCoords, FCoord CurrentCoords);
	bool CheckIfRoomFits(FRoomDataStruct* RoomDataStruct, FCoord CurrentCoords, int RoomAngle);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int CounterToSpawn = 5000;
	std::vector<std::vector<std::vector<int>>> Matrix;
	//TArray<FRoomDataToSpawnStruct*> TempRoomsToSpawnSet;
	TArray<FString> TempRoomNames_Array;
	TArray<FVector> TempVectorsToSpawn_Array;
	TArray<FRotator> TempRotatorsToSpawn_Array;
	size_t NumberOfRows;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
