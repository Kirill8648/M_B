// Copyright 2021, Aks, Spirt


#include "LevelSpawner3D_V1.h"

// Sets default values
ALevelSpawner3D_V1::ALevelSpawner3D_V1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	//пол, потолок
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
	//лево право
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
	//зад перед
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
	/*switch (Angle)
	{
	case 0:
		return InputVector;
	case 90:
		return FVector(InputVector.Y, -InputVector.X, InputVector.Z);
	case 180:
		return FVector(-InputVector.X, -InputVector.Y, InputVector.Z);
	case 270:
		return FVector(-InputVector.Y, InputVector.X, InputVector.Z);
	default:
		return InputVector;
	}*/
}

/*ALevelSpawner3D_V1::FCoord ALevelSpawner3D_V1::RotateFCoordAroundZ(FCoord InputCoord, const int Angle)
{
	switch (Angle)
	{
	case 0:
		return InputCoord;
	case 90:
		return InputCoord = {InputCoord.Y, -InputCoord.X, InputCoord.Z};
	case 180:
		return InputCoord = {-InputCoord.X, -InputCoord.Y, InputCoord.Z};
	case 270:
		return InputCoord = {-InputCoord.Y, InputCoord.X, InputCoord.Z};
	default:
		return InputCoord;
	}
}*/

int ALevelSpawner3D_V1::CalculateAngleByCoords(const FCoord PrevCoords, const FCoord CurrentCoords)
{
	if (PrevCoords.Y < CurrentCoords.Y)return 90;
	if (PrevCoords.Y > CurrentCoords.Y)return 270;
	if (PrevCoords.X < CurrentCoords.X)return 0;
	if (PrevCoords.X > CurrentCoords.X)return 180;
	return 0;
	/*if (PrevCoords.X < CurrentCoords.X)return 90;
	if (PrevCoords.X > CurrentCoords.X)return 270;
	if (PrevCoords.Y < CurrentCoords.Y)return 0;
	if (PrevCoords.Y > CurrentCoords.Y)return 180;
	return 0;*/
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

void ALevelSpawner3D_V1::SpawnRoom(UWorld* World, const FString RoomName, const FVector RoomVector,
                                   const FRotator RoomRotator)
{
	bool RoomSpawnedSuccess = false;
	FString a;
	a.AppendInt(CounterToSpawn);

	ULevelStreamingDynamic::LoadLevelInstance(World, *RoomName, RoomVector, RoomRotator, RoomSpawnedSuccess, a);
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
	//TArray<FRoomDataToSpawnStruct*> TempRoomsToSpawnSet;


	//---------------------------------BEGIN ROOM---------------------------------------
	FRoomDataStruct* TempBeginStruct = RoomsDataTable->FindRow<FRoomDataStruct>(TEXT("Begin"), ContextString, true);
	const int BeginRoomAngle = FGenericPlatformMath::Rand() % 3 * 90;
	std::string test2 = std::string(TCHAR_TO_UTF8(*TempBeginStruct->RoomNameToSpawn));
	TempRoomNames_Array.Add(TempBeginStruct->RoomNameToSpawn);
	TempVectorsToSpawn_Array.Add(FVector((MatrixXSize / 2) * LevelsGridSizeXY,
	                                     (MatrixYSize / 2) * LevelsGridSizeXY,
	                                     (MatrixZSize / 2) * LevelsGridSizeZ));
	TempRotatorsToSpawn_Array.Add(FRotator(0, BeginRoomAngle, 0));
	FRoomDataToSpawnStruct TempStructToFillBeginRoomNoPointer = {
		TempBeginStruct->RoomNameToSpawn,
		test2,
		FVector((MatrixXSize / 2) * LevelsGridSizeXY,
		        (MatrixYSize / 2) * LevelsGridSizeXY,
		        (MatrixZSize / 2) * LevelsGridSizeZ),
		FRotator(0, BeginRoomAngle, 0)
	};
	FRoomDataToSpawnStruct* TempStructToFillBeginRoom = &TempStructToFillBeginRoomNoPointer;
	//TempRoomsToSpawnSet.Add(TempStructToFillBeginRoom);

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
		//TArray<FRoomDataToSpawnStruct*> TempRoomsToSpawnSet1;
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
				FRoomDataToSpawnStruct* TempStructToFillRoom = nullptr;
				std::string test3 = std::string(TCHAR_TO_UTF8(*TempRoomStruct->RoomNameToSpawn));
				TempRoomNames_Array.Add(TempRoomStruct->RoomNameToSpawn);
				TempVectorsToSpawn_Array.Add(FVector(CurrentCoords.X * LevelsGridSizeXY,
				                                     CurrentCoords.Y * LevelsGridSizeXY,
				                                     CurrentCoords.Z * LevelsGridSizeZ));
				TempRotatorsToSpawn_Array.Add(FRotator(0, RoomAngle, 0));
				FRoomDataToSpawnStruct TempStructToFillRoomNoPointer = {
					TempRoomStruct->RoomNameToSpawn,
					test3,
					FVector(CurrentCoords.X * LevelsGridSizeXY,
					        CurrentCoords.Y * LevelsGridSizeXY,
					        CurrentCoords.Z * LevelsGridSizeZ),
					FRotator(0, RoomAngle, 0)
				};
				TempStructToFillRoom = &TempStructToFillRoomNoPointer;
				//TempRoomsToSpawnSet.Add(TempStructToFillRoom);

				for (auto& Elem : TempRoomStruct->VectorsToFill)
				{
					FVector TempCheck = RotateFVectorAroundZ(Elem, RoomAngle);
					TempCheck.X += CurrentCoords.X;
					TempCheck.Y += CurrentCoords.Y;
					TempCheck.Z += CurrentCoords.Z;
					Matrix[TempCheck.Z][TempCheck.Y][TempCheck.X] = 1;
				}

				FVector TempNearVector(RotateFVectorAroundZ(TempRoomStruct->CoordsNearExit, RoomAngle));
				FVector TempBehindVector(RotateFVectorAroundZ(TempRoomStruct->CoordsBehindExit, RoomAngle));
				/*PrevCoords = {
					TempNearVector.X + CurrentCoords.X,
					TempNearVector.Y + CurrentCoords.Y,
					TempNearVector.Z + CurrentCoords.Z
				};*/
				PrevCoords.X = TempNearVector.X + CurrentCoords.X;
				PrevCoords.Y = TempNearVector.Y + CurrentCoords.Y;
				PrevCoords.Y = TempNearVector.Y + CurrentCoords.Y;
				/*CurrentCoords = {
					TempBehindVector.X + CurrentCoords.X,
					TempBehindVector.Y + CurrentCoords.Y,
					TempBehindVector.Z + CurrentCoords.Z
				};*/
				CurrentCoords.X = TempBehindVector.X + CurrentCoords.X;
				CurrentCoords.Y = TempBehindVector.Y + CurrentCoords.Y;
				CurrentCoords.Z = TempBehindVector.Z + CurrentCoords.Z;
				/*PrevCoords = {
					static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsNearExit, RoomAngle).X) + CurrentCoords.
					X,
					static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsNearExit, RoomAngle).Y) + CurrentCoords.
					Y,
					static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsNearExit, RoomAngle).Z) + CurrentCoords.
					Z
				};
				CurrentCoords = {
					static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsBehindExit, RoomAngle).X) +
					CurrentCoords.X,
					static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsBehindExit, RoomAngle).Y) +
					CurrentCoords.Y,
					static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsBehindExit, RoomAngle).Z) +
					CurrentCoords.Z
				};*/

				//Matrix[CurrentCoords.Z][CurrentCoords.Y][CurrentCoords.X] = 1;
				//UE_LOG(LogTemp, Warning, TEXT("If code %s"), *FString(TempRoomsToSpawnSet[1]->SpawnNameStd.c_str()));
				//UE_LOG(LogTemp, Warning, TEXT("If code %s"), *TempRoomNames[1]);
			}
			//UE_LOG(LogTemp, Warning, TEXT("While code %s"), *FString(TempRoomsToSpawnSet[1]->SpawnNameStd.c_str()));
			//UE_LOG(LogTemp, Warning, TEXT("While code %s"), *TempRoomNames[1]);
		}
		//UE_LOG(LogTemp, Warning, TEXT("For code %s"), *FString(TempRoomsToSpawnSet[1]->SpawnNameStd.c_str()));
		//UE_LOG(LogTemp, Warning, TEXT("For code %s"), *TempRoomNames[1]);
		/*UE_LOG(LogTemp, Warning, TEXT("Room spawned successfully with code %s"),
					*TempRoomsToSpawnSet1[0]->SpawnName);


		//массив полностью очистить, заспавнить одну комнату, сделдать провенрку циклом таблицы
		/*TempRoomsToSpawnSet.Reset();
		while (ProcedurallyGenerateSetOfRooms())
		{
			TempRoomsToSpawnSet.Reset();
			//очистить матрицу;
		}*/
	}
	//----------------------------------------------------------------------------------


	//----------------------------------END ROOM----------------------------------------
	FRoomDataStruct* TempEndStruct = RoomsDataTable->FindRow<FRoomDataStruct>(TEXT("End"), ContextString, true);
	const int EndRoomAngle = CalculateAngleByCoords(PrevCoords, CurrentCoords);
	std::string test4 = std::string(TCHAR_TO_UTF8(*TempEndStruct->RoomNameToSpawn));
	TempRoomNames_Array.Add(TempEndStruct->RoomNameToSpawn);
	TempVectorsToSpawn_Array.Add(FVector(CurrentCoords.X * LevelsGridSizeXY,
	                                     CurrentCoords.Y * LevelsGridSizeXY,
	                                     CurrentCoords.Z * LevelsGridSizeZ));
	TempRotatorsToSpawn_Array.Add(FRotator(0, EndRoomAngle, 0));
	FRoomDataToSpawnStruct TempStructToFillEndRoomNoPointer = {
		TempEndStruct->RoomNameToSpawn,
		test4,
		FVector(CurrentCoords.X * LevelsGridSizeXY,
		        CurrentCoords.Y * LevelsGridSizeXY,
		        CurrentCoords.Z * LevelsGridSizeZ),
		FRotator(0, EndRoomAngle, 0),
	};
	FRoomDataToSpawnStruct* TempStructToFillEndRoom = &TempStructToFillEndRoomNoPointer;
	//TempRoomsToSpawnSet.Add(TempStructToFillEndRoom);

	Matrix[CurrentCoords.Z][CurrentCoords.Y][CurrentCoords.X] = 1;
	//----------------------------------------------------------------------------------


	/*UE_LOG(LogTemp, Warning, TEXT("Room spawned successfully with code %s"), *TempRoomsToSpawnSet[0]->SpawnName);
	UE_LOG(LogTemp, Warning, TEXT("Room spawned successfully with code %s"), *TempRoomsToSpawnSet[1]->SpawnName);
	UE_LOG(LogTemp, Warning, TEXT("Room spawned successfully with code %s"), *TempRoomsToSpawnSet[2]->SpawnName);*/
	/*for (auto& Elem : TempRoomsToSpawnSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("Room spawned successfully with code %s"), *Elem->SpawnName);
	}*/
	SpawnSetOfRooms(World/*, TempRoomsToSpawnSet*/);
	//PrintMatrixToLog();
	return 0;
	/*//--------------------------TEST----------------------------
	FString StringToConvertIntToName;
	//StringToConvertIntToName.AppendInt(1);
	StringToConvertIntToName.AppendInt(FGenericPlatformMath::Rand() % NumberOfRows + 1);
	FRoomDataStruct* TempRoomStruct = RoomsDataTable->FindRow<FRoomDataStruct>(
	*StringToConvertIntToName, ContextString, true);
	const int RoomAngle = CalculateAngleByCoords(PrevCoords, CurrentCoords);
	bool RoomFits = CheckIfRoomFits(TempRoomStruct, CurrentCoords, RoomAngle);
	FRoomDataToSpawnStruct* TempStructToFillRoom = nullptr;
	FRoomDataToSpawnStruct TempStructToFillRoomNoPointer = {
	TempRoomStruct->RoomNameToSpawn,
	FVector(CurrentCoords.X * LevelsGridSizeXY,
	CurrentCoords.Y * LevelsGridSizeXY,
	CurrentCoords.Z * LevelsGridSizeZ),
	FRotator(0, RoomAngle, 0)
	};
	TempStructToFillRoom = &TempStructToFillRoomNoPointer;
	TempRoomsToSpawnSet.Add(TempStructToFillRoom);
	PrevCoords = {
	static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsNearExit, RoomAngle).X) + CurrentCoords.
	X,
	static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsNearExit, RoomAngle).Y) + CurrentCoords.
	Y,
	static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsNearExit, RoomAngle).Z) + CurrentCoords.
	Z
	};
	CurrentCoords = {
	static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsBehindExit, RoomAngle).X) +
	CurrentCoords.X,
	static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsBehindExit, RoomAngle).Y) +
	CurrentCoords.Y,
	static_cast<int>(RotateFVectorAroundZ(TempRoomStruct->CoordsBehindExit, RoomAngle).Z) +
	CurrentCoords.Z
	};
	for (auto& Elem : TempRoomStruct->VectorsToFill)
	{
	FVector TempCheck = RotateFVectorAroundZ(Elem, RoomAngle);
	TempCheck.X += CurrentCoords.X;
	TempCheck.Y += CurrentCoords.Y;
	TempCheck.Z += CurrentCoords.Z;
	Matrix[TempCheck.Z][TempCheck.Y][TempCheck.X] = 1;
	}
	//----------------------END TEST------------------------*/
}


void ALevelSpawner3D_V1::SpawnSetOfRooms(UWorld* World/*, TArray<FRoomDataToSpawnStruct*> TempRoomsToSpawnSet*/)
{
	for (int32 Index = 0; Index != TempRoomNames_Array.Num(); ++Index)
	{
		SpawnRoom(World, *TempRoomNames_Array[Index], TempVectorsToSpawn_Array[Index],
		          TempRotatorsToSpawn_Array[Index]);
	}
	/*for (int32 Index = 0; Index != TempRoomsToSpawnSet.Num(); ++Index)
	{
		SpawnRoom(World, *TempRoomNames_Array[Index], TempRoomsToSpawnSet[Index]->SpawnVector,
		          TempRoomsToSpawnSet[Index]->SpawnRotator);
	}*/
	/*for (auto Elem : TempRoomsToSpawnSet)
	{
		SpawnRoom(World, *Elem->SpawnName, Elem->SpawnVector, Elem->SpawnRotator);
	}*/
}

// Called when the game starts or when spawned
void ALevelSpawner3D_V1::BeginPlay()
{
	Super::BeginPlay();

	/*static ConstructorHelpers::FObjectFinder<UDataTable> RoomsToSpawnDataObject(
		TEXT("DataTable'/Game/Data/RoomsToSpawn_DataTable.RoomsToSpawn_DataTable'"));
	if (RoomsToSpawnDataObject.Succeeded())
	{
		RoomsDataTable = RoomsToSpawnDataObject.Object;
	}*/


	// Calculate NumberOfRows
	if (RoomsDataTable)
	{
		const TArray<TArray<FString>> TempArr = RoomsDataTable->GetTableData();
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
		//TempRoomsToSpawnSet.Reset();
		TempRoomNames_Array.Reset();
		TempVectorsToSpawn_Array.Reset();
		TempRotatorsToSpawn_Array.Reset();
		SetMatrix();
		Attempts++;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
	                                 FString::Printf(TEXT("Attempts to generate: %d"), Attempts));
}

// Called every frame
void ALevelSpawner3D_V1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
