// Copyright 2021, Aks, Spirt


#include "LevelSpawner3D_V1.h"

// Sets default values
ALevelSpawner3D_V1::ALevelSpawner3D_V1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	/*static ConstructorHelpers::FObjectFinder<UDataTable> RoomsToSpawnDataObject(
		TEXT("DataTable'/Game/Data/Rooms_DataTable_Final.Rooms_DataTable_Final'"));
	if (RoomsToSpawnDataObject.Succeeded())
	{
		RoomsDataTable = RoomsToSpawnDataObject.Object;
	}*/
}

void ALevelSpawner3D_V1::SetMatrix()
{
	for (size_t i = 0; i < MatrixZSize; i++)
	{
		std::vector<std::vector<int>> Temp_Mat;
		for (size_t j = 0; j < MatrixYSize; j++)
		{
			std::vector<int> Temp_Mat1;
			for (size_t k = 0; k < MatrixXSize; k++)
			{
				Temp_Mat1.push_back(0);
			}
			Temp_Mat.push_back(Temp_Mat1);
		}
		Matrix.push_back(Temp_Mat);
	}
	// floor, roof (пол, потолок)
	for (size_t i = 0; i < MatrixYSize; i++)
	{
		for (size_t j = 0; j < MatrixXSize; j++)
		{
			for (int k = 0; k < MatrixBorderSize; k++)
			{
				Matrix[k][i][j] = 1;
				Matrix[MatrixZSize - k - 1][i][j] = 1;
			}
		}
	}
	// left, right (лево право)
	for (size_t i = 0; i < MatrixZSize; i++)
	{
		for (size_t j = 0; j < MatrixXSize; j++)
		{
			for (int k = 0; k < MatrixBorderSize; k++)
			{
				Matrix[i][k][j] = 1;
				Matrix[i][MatrixYSize - k - 1][j] = 1;
			}
		}
	}
	// back, forward (зад перед)
	for (size_t i = 0; i < MatrixZSize; i++)
	{
		for (size_t j = 0; j < MatrixYSize; j++)
		{
			for (int k = 0; k < MatrixBorderSize; k++)
			{
				Matrix[i][j][k] = 1;
				Matrix[i][j][MatrixXSize - k - 1] = 1;
			}
		}
	}
}

void ALevelSpawner3D_V1::PrintMatrixToLog()
{
	for (size_t i = 0; i < MatrixZSize; i++)
	{
		for (size_t j = 0; j < MatrixYSize; j++)
		{
			FString Temp;
			for (size_t k = 0; k < MatrixXSize; k++)
			{
				Temp.AppendInt(Matrix[i][j][k]);
			}
			UE_LOG(LogTemp, Display, TEXT("%s"), *Temp);
		}
		UE_LOG(LogTemp, Display, TEXT("----------"));
	}
}

void ALevelSpawner3D_V1::PrintSpawnedRoomNames()
{
	UE_LOG(LogTemp, Display, TEXT("Spawned level names:"))
	for (auto Elem : RoomNamesToUnload)
	{
		UE_LOG(LogTemp, Display, TEXT("%t"), *Elem.ToString());
	}
}

FVector ALevelSpawner3D_V1::RotateFVectorAroundZ(const FVector InputVector, const int Angle)
{
	switch (Angle)
	{
	case 0:
		return InputVector;
	case 90:
		return FVector(-InputVector.Y, InputVector.X, InputVector.Z);
	case 180:
		return FVector(-InputVector.X, -InputVector.Y, InputVector.Z);
	case 270:
		return FVector(InputVector.Y, -InputVector.X, InputVector.Z);
	default:
		return InputVector;
	}
}

int ALevelSpawner3D_V1::CalculateAngleByCoords(const FCoord PrevCoords, const FCoord CurrentCoords)
{
	if (PrevCoords.Y < CurrentCoords.Y)return 90;
	if (PrevCoords.Y > CurrentCoords.Y)return 270;
	if (PrevCoords.X < CurrentCoords.X)return 0;
	if (PrevCoords.X > CurrentCoords.X)return 180;
	return 0;
}

bool ALevelSpawner3D_V1::CheckIfRoomFits(FRoomDataStruct* RoomDataStruct, const FCoord CurrentCoords,
                                         const int RoomAngle)
{
	if (!RoomDataStruct->VectorsToFill.IsEmpty())
		for (auto& Elem : RoomDataStruct->VectorsToFill)
		{
			FVector TempCheck = RotateFVectorAroundZ(Elem, RoomAngle);
			TempCheck.X += CurrentCoords.X;
			TempCheck.Y += CurrentCoords.Y;
			TempCheck.Z += CurrentCoords.Z;
			if (Matrix[TempCheck.Z][TempCheck.Y][TempCheck.X] != 0) return false;
		}

	if (!RoomDataStruct->AdditionalVectorsToCheck.IsEmpty())
		for (auto& Elem : RoomDataStruct->AdditionalVectorsToCheck)
		{
			FVector TempCheck = RotateFVectorAroundZ(Elem, RoomAngle);
			TempCheck.X += CurrentCoords.X;
			TempCheck.Y += CurrentCoords.Y;
			TempCheck.Z += CurrentCoords.Z;
			if (Matrix[TempCheck.Z][TempCheck.Y][TempCheck.X] != 0) return false;
		}

	if (!RoomDataStruct->CoordsBehindExit.IsZero())
	{
		FVector TempCheck = RotateFVectorAroundZ(RoomDataStruct->CoordsBehindExit, RoomAngle);
		TempCheck.X += CurrentCoords.X;
		TempCheck.Y += CurrentCoords.Y;
		TempCheck.Z += CurrentCoords.Z;
		if (Matrix[TempCheck.Z][TempCheck.Y][TempCheck.X] != 0) return false;
	}
	return true;
}

void ALevelSpawner3D_V1::RespawnAllLevels()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("Tick");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;
	UGameplayStatics::UnloadStreamLevel(
		GetWorld(), RoomNamesToUnload[FGenericPlatformMath::Rand() % RoomNamesToUnload.Num() - 2], LatentInfo,
		false);

	/*UWorld* World = GetWorld();

	UnloadAllSpawnedLevels(World);
	TempRoomNames_Array.Reset();
	TempVectorsToSpawn_Array.Reset();
	TempRotatorsToSpawn_Array.Reset();
	RoomNamesToUnload.Reset();
	SetMatrix();

	while (ProcedurallyGenerateSetOfRooms(World))
	{
		TempRoomNames_Array.Reset();
		TempVectorsToSpawn_Array.Reset();
		TempRotatorsToSpawn_Array.Reset();
		RoomNamesToUnload.Reset();
		SetMatrix();
	}*/
}


void ALevelSpawner3D_V1::SpawnRoom(UWorld* World, const FString RoomName, const FVector RoomVector,
                                   const FRotator RoomRotator)
{
	bool RoomSpawnedSuccess = false;
	FString a;
	a.AppendInt(CounterToSpawn);

	ULevelStreamingDynamic::LoadLevelInstance(World, *RoomName, RoomVector, RoomRotator, RoomSpawnedSuccess, a);

	FString TempRoomNameToUnload;
	RoomName.Split("/", &TempRoomNameToUnload, nullptr, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	TempRoomNameToUnload.Append("/UEDPIE_0_");
	TempRoomNameToUnload.Append(a);
	RoomNamesToUnload.Add(*TempRoomNameToUnload);

	if (RoomSpawnedSuccess)
	{
		UE_LOG(LogTemp, Display, TEXT("Room spawned successfully with code %s"), *a);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Room spawn with code %s failed"), *a);
	}
	CounterToSpawn--;
}

int ALevelSpawner3D_V1::ProcedurallyGenerateSetOfRooms(UWorld* World)
{
	static const FString ContextString(TEXT(""));


	//---------------------------------BEGIN ROOM---------------------------------------
	FRoomDataStruct* TempBeginStruct = RoomsDataTable->FindRow<FRoomDataStruct>(TEXT("Begin"), ContextString, true);
	const int BeginRoomAngle = FGenericPlatformMath::Rand() % 3 * 90;
	//std::string test2 = std::string(TCHAR_TO_UTF8(*TempBeginStruct->RoomNameToSpawn));
	TempRoomNames_Array.Add(TempBeginStruct->RoomNameToSpawn);
	TempVectorsToSpawn_Array.Add(FVector((MatrixXSize / 2) * LevelsGridSizeXY,
	                                     (MatrixYSize / 2) * LevelsGridSizeXY,
	                                     (MatrixZSize / 2) * LevelsGridSizeZ));
	TempRotatorsToSpawn_Array.Add(FRotator(0, BeginRoomAngle, 0));

	// Coords for first room (after BeginRoom)
	FCoord PrevCoords = {MatrixXSize / 2, MatrixYSize / 2, MatrixZSize / 2};
	FCoord CurrentCoords = {
		RotateFVectorAroundZ(TempBeginStruct->CoordsBehindExit, BeginRoomAngle).X + MatrixXSize / 2,
		RotateFVectorAroundZ(TempBeginStruct->CoordsBehindExit, BeginRoomAngle).Y + MatrixYSize / 2,
		RotateFVectorAroundZ(TempBeginStruct->CoordsBehindExit, BeginRoomAngle).Z + MatrixZSize / 2
	};
	Matrix[MatrixZSize / 2][MatrixYSize / 2][MatrixXSize / 2] = 1;
	//----------------------------------------------------------------------------------


	//---------------------------------ROOM CYCLE---------------------------------------
	for (int i = 0; i < NumberOfRoomsToSpawn - 2; i++)
	{
		bool RoomFits;
		bool ReturnFlag = false;

		for (int j = 1; j <= NumberOfRows; j++)
		{
			FString StringToConvertIntToName;

			StringToConvertIntToName.AppendInt(j);
			FRoomDataStruct* TempRoomStruct = RoomsDataTable->FindRow<FRoomDataStruct>(
				*StringToConvertIntToName, ContextString, true);
			const int RoomAngle = CalculateAngleByCoords(PrevCoords, CurrentCoords);
			RoomFits = CheckIfRoomFits(TempRoomStruct, CurrentCoords, RoomAngle);
			if (RoomFits) break;
			if (j == NumberOfRows) ReturnFlag = true;
		}

		if (ReturnFlag) return 1;

		RoomFits = false;
		while (!RoomFits)
		{
			FString StringToConvertIntToName;

			StringToConvertIntToName.AppendInt(FGenericPlatformMath::Rand() % NumberOfRows + 1);
			FRoomDataStruct* TempRoomStruct = RoomsDataTable->FindRow<FRoomDataStruct>(
				*StringToConvertIntToName, ContextString, true);
			const int RoomAngle = CalculateAngleByCoords(PrevCoords, CurrentCoords);
			RoomFits = CheckIfRoomFits(TempRoomStruct, CurrentCoords, RoomAngle);
			if (RoomFits)
			{
				TempRoomNames_Array.Add(TempRoomStruct->RoomNameToSpawn);
				TempVectorsToSpawn_Array.Add(FVector(CurrentCoords.X * LevelsGridSizeXY,
				                                     CurrentCoords.Y * LevelsGridSizeXY,
				                                     CurrentCoords.Z * LevelsGridSizeZ));
				TempRotatorsToSpawn_Array.Add(FRotator(0, RoomAngle, 0));

				for (auto& Elem : TempRoomStruct->VectorsToFill)
				{
					FVector TempCheck = RotateFVectorAroundZ(Elem, RoomAngle);
					TempCheck.X += CurrentCoords.X;
					TempCheck.Y += CurrentCoords.Y;
					TempCheck.Z += CurrentCoords.Z;
					Matrix[TempCheck.Z][TempCheck.Y][TempCheck.X] = 1;
				}

				const FVector TempNearVector(RotateFVectorAroundZ(TempRoomStruct->CoordsNearExit, RoomAngle));
				const FVector TempBehindVector(RotateFVectorAroundZ(TempRoomStruct->CoordsBehindExit, RoomAngle));

				PrevCoords.X = TempNearVector.X + CurrentCoords.X;
				PrevCoords.Y = TempNearVector.Y + CurrentCoords.Y;
				PrevCoords.Z = TempNearVector.Z + CurrentCoords.Z;

				CurrentCoords.X = TempBehindVector.X + CurrentCoords.X;
				CurrentCoords.Y = TempBehindVector.Y + CurrentCoords.Y;
				CurrentCoords.Z = TempBehindVector.Z + CurrentCoords.Z;
			}
		}
	}
	//----------------------------------------------------------------------------------


	//----------------------------------END ROOM----------------------------------------
	FRoomDataStruct* TempEndStruct = RoomsDataTable->FindRow<FRoomDataStruct>(TEXT("End"), ContextString, true);
	const int EndRoomAngle = CalculateAngleByCoords(PrevCoords, CurrentCoords);
	TempRoomNames_Array.Add(TempEndStruct->RoomNameToSpawn);
	TempVectorsToSpawn_Array.Add(FVector(CurrentCoords.X * LevelsGridSizeXY,
	                                     CurrentCoords.Y * LevelsGridSizeXY,
	                                     CurrentCoords.Z * LevelsGridSizeZ));
	TempRotatorsToSpawn_Array.Add(FRotator(0, EndRoomAngle, 0));

	/*FRoomDataToSpawnStruct TempStructToFillEndRoomNoPointer = {
		TempEndStruct->RoomNameToSpawn,
		test4,
		FVector(CurrentCoords.X * LevelsGridSizeXY,
		        CurrentCoords.Y * LevelsGridSizeXY,
		        CurrentCoords.Z * LevelsGridSizeZ),
		FRotator(0, EndRoomAngle, 0),
	};
	FRoomDataToSpawnStruct* TempStructToFillEndRoom = &TempStructToFillEndRoomNoPointer;
	//TempRoomsToSpawnSet.Add(TempStructToFillEndRoom);*/

	Matrix[CurrentCoords.Z][CurrentCoords.Y][CurrentCoords.X] = 1;
	//----------------------------------------------------------------------------------


	SpawnSetOfRooms(World);
	return 0;
}


void ALevelSpawner3D_V1::SpawnSetOfRooms(UWorld* World)
{
	for (int32 Index = 0; Index != TempRoomNames_Array.Num(); ++Index)
	{
		SpawnRoom(World, *TempRoomNames_Array[Index], TempVectorsToSpawn_Array[Index],
		          TempRotatorsToSpawn_Array[Index]);
	}
}

void ALevelSpawner3D_V1::UnloadAllSpawnedLevels(UWorld* World)
{
	//ULevelStreaming* LevelStreaming = nullptr;
	//UGameplayStatics* LevelStreaming;

	//LevelStreaming->SetIsRequestingUnloadAndRemoval(true);
	PrintSpawnedRoomNames();
	for (auto& Elem : RoomNamesToUnload)
	{
		const FLatentActionInfo LatentInfo;
		/*LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = "UnloadAllSpawnedLevels";
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = 0;*/
		UGameplayStatics::UnloadStreamLevel(World, Elem, LatentInfo, false);
	}

	/*PrintSpawnedRoomNames();
	const FLatentActionInfo LatentInfo;
	UGameplayStatics::UnloadStreamLevel(World, *RoomNamesToUnload[0], LatentInfo, false);
	UE_LOG(LogTemp, Warning, TEXT("Unloaded level"), *RoomNamesToUnload[0]);
	UGameplayStatics::UnloadStreamLevel(World, *RoomNamesToUnload[1], LatentInfo, false);
	UE_LOG(LogTemp, Warning, TEXT("Unloaded level"), *RoomNamesToUnload[1]);
	UGameplayStatics::UnloadStreamLevel(World, *RoomNamesToUnload[2], LatentInfo, false);
	UE_LOG(LogTemp, Warning, TEXT("Unloaded level"), *RoomNamesToUnload[2]);
	UGameplayStatics::UnloadStreamLevel(World, *RoomNamesToUnload[3], LatentInfo, false);
	UE_LOG(LogTemp, Warning, TEXT("Unloaded level"), *RoomNamesToUnload[3]);
	UGameplayStatics::UnloadStreamLevel(World, *RoomNamesToUnload[4], LatentInfo, false);
	UE_LOG(LogTemp, Warning, TEXT("Unloaded level"), *RoomNamesToUnload[4]);*/
}

// Called when the game starts or when spawned
void ALevelSpawner3D_V1::BeginPlay()
{
	Super::BeginPlay();

	// Calculate NumberOfRows
	if (RoomsDataTable)
	{
		/*const TArray<TArray<FString>> TempArr = RoomsDataTable->GetTableData();
		NumberOfRows = TempArr.Num() - 1 - 2;*/

		const TArray<FName> TempArr = RoomsDataTable->GetRowNames();
		NumberOfRows = TempArr.Num() - 1 - 2;
	}
	if (NumberOfRows)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
		                                 FString::Printf(TEXT("Number of rows in DataTable = %llu"), NumberOfRows));
	else GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, "RoomsDataTable = null");

	UWorld* World = GetWorld();
	SetMatrix();
	int Attempts = 1;
	while (ProcedurallyGenerateSetOfRooms(World))
	{
		TempRoomNames_Array.Reset();
		TempVectorsToSpawn_Array.Reset();
		TempRotatorsToSpawn_Array.Reset();
		RoomNamesToUnload.Reset();
		SetMatrix();
		Attempts++;
	}
	//PrintSpawnedRoomNames();

	/*FTimerHandle handle;
	float delayTime = 5.0;
	GetWorld()->GetTimerManager().SetTimer(handle, [this]()
	{
		bool IsReloading = false;
	}, delayTime, 1);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
	                                 FString::Printf(TEXT("Таймер прошел")));*/
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
	                                 FString::Printf(TEXT("Attempts to generate: %d"), Attempts));
}

// Called every frame
void ALevelSpawner3D_V1::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
