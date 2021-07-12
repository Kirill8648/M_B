// Copyright 2021, Aks, Spirt


#include "LevelSpawner_V1.h"

// Sets default values
ALevelSpawner_V1::ALevelSpawner_V1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

void ALevelSpawner_V1::DrawRoomCreationMassage(bool Check, FString RoomName) {
	Check ? GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, "Room " + RoomName + " spawned succesfully") :
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "Room spawn with path " + RoomName + " failed");
}

void ALevelSpawner_V1::SpawnRoom(UWorld* world, FString RoomName, FVector RoomVector, FRotator RoomRotator, int UniqueIndex)
{
	bool RoomSpawnedSuccess;
	FString a;
	//a.AppendInt(FMath::RandRange(0, 999999));
	a.AppendInt(UniqueIndex);
	ULevelStreamingDynamic::LoadLevelInstance(world, *RoomName, RoomVector, RoomRotator, RoomSpawnedSuccess, a);
	DrawRoomCreationMassage(RoomSpawnedSuccess, RoomName);
}

void ALevelSpawner_V1::RecursivePath(int OldIndexX, int OldIndexY, int IndexX, int IndexY, UWorld* world)
{
	if (matrix[IndexX][IndexY] == 1)
	{
		FRotator Cell1RoomRotator(0.f);
		FVector Cell1RoomVector(IndexY * LevelsGridSize, IndexX * LevelsGridSize, 0);
		unsigned short int Cell1RoomDirections[] = { 0,0,0,0 };
		int NewIndexX = 0;
		int NewIndexY = 0;
		if ((matrix[IndexX + 1][IndexY] != 0) && (matrix[IndexX - 1][IndexY] != 0)) //прямая, вертикально направлена
		{
			if (OldIndexX > IndexX) { Cell1RoomRotator.Add(0, -90, 0); NewIndexX = IndexX - 1; NewIndexY = IndexY; }
			else if (OldIndexX < IndexX) { Cell1RoomRotator.Add(0, 90, 0); NewIndexX = IndexX + 1; NewIndexY = IndexY; }
			Cell1RoomDirections[0] = 2;
			Cell1RoomDirections[2] = 1;
		}
		else if ((matrix[IndexX][IndexY + 1] != 0) && (matrix[IndexX][IndexY - 1] != 0)) //прямая, горизонтально направлена
		{
			if (OldIndexY > IndexY) { Cell1RoomRotator.Add(0, 180, 0); NewIndexX = IndexX; NewIndexY = IndexY - 1; }
			else if (OldIndexY < IndexY) { Cell1RoomRotator.Add(0, 0, 0); NewIndexX = IndexX; NewIndexY = IndexY + 1; }
			Cell1RoomDirections[0] = 2;
			Cell1RoomDirections[2] = 1;
		}
		else if ((matrix[IndexX - 1][IndexY] != 0) && (matrix[IndexX][IndexY - 1] != 0)) //лево и верх
		{
			if (OldIndexX < IndexX) //вход сверху
			{
				Cell1RoomRotator.Add(0, 90, 0);
				Cell1RoomDirections[1] = 2;
				Cell1RoomDirections[2] = 1;
				NewIndexX = IndexX; NewIndexY = IndexY - 1;
			}
			else if (OldIndexY < IndexY) //вход слева
			{
				Cell1RoomRotator.Add(0, 0, 0);
				Cell1RoomDirections[2] = 1;
				Cell1RoomDirections[3] = 2;
				NewIndexX = IndexX - 1; NewIndexY = IndexY;
			}
		}
		else if ((matrix[IndexX - 1][IndexY] != 0) && (matrix[IndexX][IndexY + 1] != 0)) //право и верх
		{
			if (OldIndexX < IndexX) //вход сверху
			{
				Cell1RoomRotator.Add(0, 90, 0);
				Cell1RoomDirections[2] = 1;
				Cell1RoomDirections[3] = 2;
				NewIndexX = IndexX; NewIndexY = IndexY + 1;
			}
			else if (OldIndexY > IndexY) //вход справа
			{
				Cell1RoomRotator.Add(0, 180, 0);
				Cell1RoomDirections[1] = 2;
				Cell1RoomDirections[2] = 1;
				NewIndexX = IndexX - 1; NewIndexY = IndexY;
			}
		}
		else if ((matrix[IndexX + 1][IndexY] != 0) && (matrix[IndexX][IndexY + 1] != 0)) //право и низ
		{
			if (OldIndexX > IndexX) //вход снизу
			{
				Cell1RoomRotator.Add(0, -90, 0);
				Cell1RoomDirections[1] = 2;
				Cell1RoomDirections[2] = 1;
				NewIndexX = IndexX; NewIndexY = IndexY + 1;
			}
			else if (OldIndexY > IndexY) //вход справа
			{
				Cell1RoomRotator.Add(0, 180, 0);
				Cell1RoomDirections[2] = 1;
				Cell1RoomDirections[3] = 2;
				NewIndexX = IndexX + 1; NewIndexY = IndexY;
			}
		}
		else if ((matrix[IndexX + 1][IndexY] != 0) && (matrix[IndexX][IndexY - 1] != 0)) //лево и низ
		{
			if (OldIndexX > IndexX) //вход снизу
			{
				Cell1RoomRotator.Add(0, -90, 0);
				Cell1RoomDirections[2] = 1;
				Cell1RoomDirections[3] = 2;
				NewIndexX = IndexX; NewIndexY = IndexY - 1;
			}
			else if (OldIndexY < IndexY) //вход слева
			{
				Cell1RoomRotator.Add(0, 0, 0);
				Cell1RoomDirections[1] = 2;
				Cell1RoomDirections[2] = 1;
				NewIndexX = IndexX + 1; NewIndexY = IndexY;
			}
		}
		Room1Cell Cell1Room(Cell1RoomDirections[0], Cell1RoomDirections[1], Cell1RoomDirections[2], Cell1RoomDirections[3]);
		FString Cell1RoomName = Cell1Room.GenerateRoomName(NumberOf1CellRooms);
		SpawnRoom(world, Cell1RoomName, Cell1RoomVector, Cell1RoomRotator, IndexX + IndexY);
		matrix[IndexX][IndexY] = 10;
		RecursivePath(IndexX, IndexY, NewIndexX, NewIndexY, world);
	}
	else if (matrix[IndexX][IndexY] == 2)
	{
		FRotator Cell2RoomRotator(0.f);
		FVector Cell2RoomVector(0.f);
		unsigned short int Cell2RoomDirections[] = { 0,0,0,0,0,0 };
		Cell2RoomDirections[3] = 1;
		int NewIndexX = 0;
		int NewIndexY = 0;
		int AdditionalIndexX = 0;
		int AdditionalIndexY = 0;
		if (matrix[IndexX][IndexY + 1] == 2) //вправо направлена
		{
			Cell2RoomVector.AddBounded(FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize, 0));
			AdditionalIndexX = IndexX;
			AdditionalIndexY = IndexY + 1;
			if (matrix[IndexX - 1][IndexY + 1] != 0) //вверх выход
			{
				Cell2RoomRotator.Add(0, 0, 0);
				NewIndexX = IndexX - 1;
				NewIndexY = IndexY + 1;
				Cell2RoomDirections[5] = 2;
			}
			else if (matrix[IndexX + 1][IndexY + 1] != 0) //вниз выход
			{
				Cell2RoomRotator.Add(0, 0, 0);
				NewIndexX = IndexX + 1;
				NewIndexY = IndexY + 1;
				Cell2RoomDirections[1] = 2;
			}
			else if (matrix[IndexX][IndexY + 2] != 0) //вправо выход
			{
				Cell2RoomRotator.Add(0, 0, 0);
				NewIndexX = IndexX;
				NewIndexY = IndexY + 2;
				Cell2RoomDirections[0] = 2;
			}
		}
		else if (matrix[IndexX][IndexY - 1] == 2) //влево направлена
		{
			Cell2RoomVector.AddBounded(FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize, 0));
			AdditionalIndexX = IndexX;
			AdditionalIndexY = IndexY - 1;
			if (matrix[IndexX - 1][IndexY - 1] != 0) //вверх выход
			{
				Cell2RoomRotator.Add(0, 180, 0);
				NewIndexX = IndexX - 1;
				NewIndexY = IndexY - 1;
				Cell2RoomDirections[1] = 2;
			}
			else if (matrix[IndexX + 1][IndexY - 1] != 0) //вниз выход
			{
				Cell2RoomRotator.Add(0, 180, 0);
				NewIndexX = IndexX + 1;
				NewIndexY = IndexY - 1;
				Cell2RoomDirections[5] = 2;
			}
			else if (matrix[IndexX][IndexY - 2] != 0) //влево выход
			{
				Cell2RoomRotator.Add(0, 180, 0);
				NewIndexX = IndexX;
				NewIndexY = IndexY - 2;
				Cell2RoomDirections[0] = 2;
			}
		}
		else if (matrix[IndexX + 1][IndexY] == 2) //вниз направлена
		{
			Cell2RoomVector.AddBounded(FVector(IndexY * LevelsGridSize, IndexX * LevelsGridSize + LevelsGridSize / 2, 0));
			AdditionalIndexX = IndexX + 1;
			AdditionalIndexY = IndexY;
			if (matrix[IndexX + 1][IndexY + 1] != 0) //вправо выход
			{
				Cell2RoomRotator.Add(0, 90, 0);
				NewIndexX = IndexX + 1;
				NewIndexY = IndexY + 1;
				Cell2RoomDirections[5] = 2;
			}
			else if (matrix[IndexX + 1][IndexY - 1] != 0) //влево выход
			{
				Cell2RoomRotator.Add(0, 90, 0);
				NewIndexX = IndexX + 1;
				NewIndexY = IndexY - 1;
				Cell2RoomDirections[1] = 2;
			}
			else if (matrix[IndexX + 2][IndexY] != 0) //вниз выход
			{
				Cell2RoomRotator.Add(0, 90, 0);
				NewIndexX = IndexX + 2;
				NewIndexY = IndexY;
				Cell2RoomDirections[0] = 2;
			}
		}
		else if (matrix[IndexX - 1][IndexY] == 2) //вверх направлена
		{
			Cell2RoomVector.AddBounded(FVector(IndexY * LevelsGridSize, IndexX * LevelsGridSize - LevelsGridSize / 2, 0));
			AdditionalIndexX = IndexX - 1;
			AdditionalIndexY = IndexY;
			if (matrix[IndexX - 1][IndexY + 1] != 0) //вправо выход
			{
				Cell2RoomRotator.Add(0, -90, 0);
				NewIndexX = IndexX - 1;
				NewIndexY = IndexY + 1;
				Cell2RoomDirections[1] = 2;
			}
			else if (matrix[IndexX - 1][IndexY - 1] != 0) //влево выход
			{
				Cell2RoomRotator.Add(0, -90, 0);
				NewIndexX = IndexX - 1;
				NewIndexY = IndexY - 1;
				Cell2RoomDirections[5] = 2;
			}
			else if (matrix[IndexX - 2][IndexY] != 0) //вверх выход
			{
				Cell2RoomRotator.Add(0, -90, 0);
				NewIndexX = IndexX - 2;
				NewIndexY = IndexY;
				Cell2RoomDirections[0] = 2;
			}
		}
		Room2Cells Cell2Room(Cell2RoomDirections[0], Cell2RoomDirections[1], Cell2RoomDirections[2], Cell2RoomDirections[3], Cell2RoomDirections[4], Cell2RoomDirections[5]);
		FString Cell2RoomName = Cell2Room.GenerateRoomName(NumberOf2CellRooms);
		SpawnRoom(world, Cell2RoomName, Cell2RoomVector, Cell2RoomRotator, IndexX + IndexY);
		matrix[IndexX][IndexY] = 10;
		matrix[AdditionalIndexX][AdditionalIndexY] = 10;
		RecursivePath(AdditionalIndexX, AdditionalIndexY, NewIndexX, NewIndexY, world);
	}
	else if (matrix[IndexX][IndexY] == 4)
	{
		FRotator Cell4RoomRotator(0.f);
		FVector Cell4RoomVector(0.f);
		unsigned short int Cell4RoomDirections[] = { 0,0,0,0,0,0,0,0 };
		int NewIndexX = 0;
		int NewIndexY = 0;
		int AdditionalIndexX = 0;
		int AdditionalIndexY = 0;
		if (OldIndexY < IndexY) //если вход слева 
		{
			if (matrix[IndexX + 1][IndexY] == 4) //вариант с правым выходом
			{
				Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0));
				Cell4RoomRotator.Add(0, 0, 0);
				NewIndexX = IndexX + 1;
				NewIndexY = IndexY + 2;
				AdditionalIndexX = IndexX + 1;
				AdditionalIndexY = IndexY + 1;
				Cell4RoomDirections[3] = 2;
				Cell4RoomDirections[7] = 1;
			}
			else if (matrix[IndexX - 1][IndexY] == 4) //вариант с левым выходом
			{
				Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0));
				Cell4RoomRotator.Add(0, 0, 0);
				NewIndexX = IndexX - 1;
				NewIndexY = IndexY + 2;
				AdditionalIndexX = IndexX - 1;
				AdditionalIndexY = IndexY + 1;
				Cell4RoomDirections[2] = 2;
				Cell4RoomDirections[6] = 1;
			}
		}
		else if (OldIndexY > IndexY) //если вход справа
		{
			if (matrix[IndexX - 1][IndexY] == 4) //вариант с правым выходом
			{
				Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0));
				Cell4RoomRotator.Add(0, 180, 0);
				NewIndexX = IndexX - 1;
				NewIndexY = IndexY - 2;
				AdditionalIndexX = IndexX - 1;
				AdditionalIndexY = IndexY - 1;
				Cell4RoomDirections[3] = 2;
				Cell4RoomDirections[7] = 1;
			}
			else if (matrix[IndexX + 1][IndexY] == 4) //вариант с левым выходом
			{
				Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0));
				Cell4RoomRotator.Add(0, 180, 0);
				NewIndexX = IndexX + 1;
				NewIndexY = IndexY - 2;
				AdditionalIndexX = IndexX + 1;
				AdditionalIndexY = IndexY - 1;
				Cell4RoomDirections[2] = 2;
				Cell4RoomDirections[6] = 1;
			}
		}
		else if (OldIndexX < IndexX) //если вход сверху
		{
			if (matrix[IndexX][IndexY - 1] == 4) //вариант с правым выходом
			{
				Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0));
				Cell4RoomRotator.Add(0, 90, 0);
				NewIndexX = IndexX + 2;
				NewIndexY = IndexY - 1;
				AdditionalIndexX = IndexX + 1;
				AdditionalIndexY = IndexY - 1;
				Cell4RoomDirections[3] = 2;
				Cell4RoomDirections[7] = 1;
			}
			else if (matrix[IndexX][IndexY + 1] == 4) //вариант с левым выходом
			{
				Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0));
				Cell4RoomRotator.Add(0, 90, 0);
				NewIndexX = IndexX + 2;
				NewIndexY = IndexY + 1;
				AdditionalIndexX = IndexX + 1;
				AdditionalIndexY = IndexY + 1;
				Cell4RoomDirections[2] = 2;
				Cell4RoomDirections[6] = 1;
			}
		}
		else if (OldIndexX > IndexX) //если вход снизу
		{
			if (matrix[IndexX][IndexY + 1] == 4) //вариант с правым выходом
			{
				Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0));
				Cell4RoomRotator.Add(0, -90, 0);
				NewIndexX = IndexX - 2;
				NewIndexY = IndexY + 1;
				AdditionalIndexX = IndexX - 1;
				AdditionalIndexY = IndexY + 1;
				Cell4RoomDirections[3] = 2;
				Cell4RoomDirections[7] = 1;
			}
			else if (matrix[IndexX][IndexY - 1] == 4) //вариант с левым выходом
			{
				Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0));
				Cell4RoomRotator.Add(0, -90, 0);
				NewIndexX = IndexX - 2;
				NewIndexY = IndexY - 1;
				AdditionalIndexX = IndexX - 1;
				AdditionalIndexY = IndexY - 1;
				Cell4RoomDirections[2] = 2;
				Cell4RoomDirections[6] = 1;
			}
		}
		Room4Cells Cell4Room(Cell4RoomDirections[0], Cell4RoomDirections[1], Cell4RoomDirections[2], Cell4RoomDirections[3], Cell4RoomDirections[4], Cell4RoomDirections[5], Cell4RoomDirections[6], Cell4RoomDirections[7]);
		FString Cell4RoomName = Cell4Room.GenerateRoomName(NumberOf4CellRooms);
		SpawnRoom(world, Cell4RoomName, Cell4RoomVector, Cell4RoomRotator, IndexX + IndexY);
		matrix[IndexX][IndexY] = 10;
		matrix[AdditionalIndexX][AdditionalIndexY] = 10; //заполняем только 2 клетки вместо четырех, пока так работает. потом можно переделать
		RecursivePath(AdditionalIndexX, AdditionalIndexY, NewIndexX, NewIndexY, world);
	}
	else if (matrix[IndexX][IndexY] == 8)
	{
		FRotator BeginRoomRotator(0);
		FVector BeginRoomVector(IndexY * LevelsGridSize, IndexX * LevelsGridSize, 0);
		int NewIndexX = 0;
		int NewIndexY = 0;
		if ((matrix[IndexX + 1][IndexY] != 0)) //выход вниз
		{
			BeginRoomRotator.Add(0, 90, 0);
			NewIndexX = IndexX + 1;
			NewIndexY = IndexY;
		}
		else if (matrix[IndexX - 1][IndexY] != 0) //выход вверх
		{
			BeginRoomRotator.Add(0, -90, 0);
			NewIndexX = IndexX - 1;
			NewIndexY = IndexY;
		}
		else if (matrix[IndexX][IndexY + 1] != 0) //выход вправо
		{
			BeginRoomRotator.Add(0, 0, 0);
			NewIndexX = IndexX;
			NewIndexY = IndexY + 1;
		}
		else if (matrix[IndexX][IndexY - 1] != 0) //выход влево
		{
			BeginRoomRotator.Add(0, 180, 0);
			NewIndexX = IndexX;
			NewIndexY = IndexY - 1;
		}
		Room1Cell BeginRoom(2, 0, 0, 0);
		FString BeginRoomName = BeginRoom.GenerateRoomName(NumberOfBeginRooms);
		SpawnRoom(world, BeginRoomName, BeginRoomVector, BeginRoomRotator, IndexX + IndexY);
		matrix[IndexX][IndexY] = 10;
		RecursivePath(IndexX, IndexY, NewIndexX, NewIndexY, world);
	}
	else if (matrix[IndexX][IndexY] == 9)
	{
		FRotator EndRoomRotator(0.f);
		FVector EndRoomVector(IndexY * LevelsGridSize, IndexX * LevelsGridSize, 0);
		if (OldIndexX > IndexX) EndRoomRotator.Add(0, -90, 0); //вход снизу
		else if (OldIndexX < IndexX) EndRoomRotator.Add(0, 90, 0); //вход сверху
		else if (OldIndexY > IndexY) EndRoomRotator.Add(0, 180, 0); //вход справа
		else if (OldIndexY < IndexY) EndRoomRotator.Add(0, 0, 0); //вход слева
		Room1Cell EndRoom(0, 0, 1, 0);
		FString EndRoomName = EndRoom.GenerateRoomName(NumberOfEndRooms);
		SpawnRoom(world, EndRoomName, EndRoomVector, EndRoomRotator, IndexX + IndexY);
		matrix[IndexX][IndexY] = 10;
		return;
	}
}

// Called when the game starts or when spawned
void ALevelSpawner_V1::BeginPlay()
{
	Super::BeginPlay();
	if (NumberOfBeginRooms < 1 || NumberOf1CellRooms < 1 || NumberOf2CellRooms < 1 || NumberOfEndRooms < 1/* || NumberOf4CellRooms<1*/)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Yellow, "BEGINPLAY CALLED SEVERAL TIMES, SOME OF THE UPROPERTIES EQUALS 0");
		return;
	}
	UWorld* world = GetWorld();
	if (world) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "World found");
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, "World not found");
		return;
	}

	UGameInstanceToSave* const TempGameInstance = world != NULL ? world->GetGameInstance<UGameInstanceToSave>() : NULL;
	if (TempGameInstance) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "GameInstance found");
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, "GameInstance not found");
		return;
	}
	FGenericPlatformMath::RandInit(TempGameInstance->Seed);

	FString temp = "Generated Seed: ";
	temp.AppendInt(TempGameInstance->Seed);
	GEngine->AddOnScreenDebugMessage(-1, INFINITY, FColor::Emerald, temp);

	for (int i = 0; i < MatrixVerticalSize; i++)
	{
		std::vector<int> temp_mat;
		for (size_t j = 0; j < MatrixHorizontalSize; j++)
		{
			temp_mat.push_back('0');
		}
		matrix.push_back(temp_mat);
	}

	for (size_t i = 0; i < matrix.size(); i++)
		for (size_t j = 0; j < matrix[0].size(); j++)
			if (matrix[i][j] == 8)
			{
				RecursivePath(0, 0, i, j, world);
				goto end_loop;
			}
end_loop:;
}

// Called every frame
void ALevelSpawner_V1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

