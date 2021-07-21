// Copyright 2021, Aks, Spirt


#include "LevelSpawner_V1.h"

// Sets default values
ALevelSpawner_V1::ALevelSpawner_V1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

int ALevelSpawner_V1::procedure_gen_mega_rand_with_rand_room_int(std::vector<std::vector<int>>& mas, int number_rooms)
{
	int hero_x = mas[0].size() / 2;
	int hero_y = mas.size() / 2;

	mas[hero_y][hero_x] = 8;

	int room = -1;

	int prev_room = 0;

	int direction = FGenericPlatformMath::Rand() % 4;
	int prev_direction = 0;

	Vector prev_vec_dis{ 0,-1 };
	int lenght_room = 2;

	for (int i = 0; i < number_rooms; i++)
	{
		int flag = 0;

		Vector vec_dis{ 1,0 };

		room = FGenericPlatformMath::Rand() % 10;

		if (i == number_rooms - 1)
		{
			room = 0;
		}

		float sum_time = 0;

		if (room >= 0 && room < 9)
		{
			while (!flag)
			{
				int check_1 = obr_point_int(mas, hero_x + 1, hero_y);
				int check_2 = obr_point_int(mas, hero_x - 1, hero_y);
				int check_3 = obr_point_int(mas, hero_x, hero_y + 1);
				int check_4 = obr_point_int(mas, hero_x, hero_y - 1);

				if (check_1 > 1 && check_2 > 1 && check_3 > 1 && check_4 > 1)
				{
					return 1;
				}

				direction = FGenericPlatformMath::Rand() % 4;

				if (direction == 0)
				{
					vec_dis.x = 0;
					vec_dis.y = -1;
				}
				else if (direction == 1)
				{
					vec_dis.x = 1;
					vec_dis.y = 0;
				}
				else if (direction == 2)
				{
					vec_dis.x = 0;
					vec_dis.y = 1;
				}
				else
				{
					vec_dis.x = -1;
					vec_dis.y = 0;
				}

				if (obr_point_int(mas, hero_x + vec_dis.x, hero_y + vec_dis.y) == 1 && mas[hero_y + vec_dis.y][hero_x + vec_dis.x] == 0)
				{
					flag = 1;
				}
			}
			hero_x += vec_dis.x;
			hero_y += vec_dis.y;

			if (i != number_rooms - 1)
			{
				mas[hero_y][hero_x] = 1;

			}
			else
			{
				mas[hero_y][hero_x] = 9;

			}
		}
		else
		{
			while (!flag)
			{

				if (fun_long_room_int(mas, lenght_room, hero_x, hero_y))
				{
					return 1;
				}

				direction = FGenericPlatformMath::Rand() % 4;

				if (direction == 0)
				{
					vec_dis.x = 0;
					vec_dis.y = -1;
				}
				else if (direction == 1)
				{
					vec_dis.x = 1;
					vec_dis.y = 0;
				}
				else if (direction == 2)
				{
					vec_dis.x = 0;
					vec_dis.y = 1;
				}
				else
				{
					vec_dis.x = -1;
					vec_dis.y = 0;
				}

				if (fun_fin_long_room_int(mas, lenght_room, hero_x, hero_y, vec_dis.x, vec_dis.y))
				{
					flag = 1;
				}
			}

			change_data_int(mas, lenght_room, hero_x, hero_y, vec_dis.x, vec_dis.y);
		}

		prev_room = room;
		prev_direction = direction;
		prev_vec_dis = vec_dis;
	}

	return 0;
}

void ALevelSpawner_V1::Generation_Map_Test1_int(std::vector<std::vector<int>>& mas, int number_rooms)
{

	int N = mas.size();
	int M = mas[0].size();

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			mas[i][j] = 0;
		}
	}

	for (int i = 0; i < M; i++)
	{
		mas[0][i] = 11;
		mas[1][i] = 11;
		mas[2][i] = 11;

		mas[N - 1][i] = 11;
		mas[N - 2][i] = 11;
		mas[N - 3][i] = 11;
	}

	for (int i = 0; i < N; i++)
	{
		mas[i][0] = 11;
		mas[i][1] = 11;
		mas[i][2] = 11;

		mas[i][M - 1] = 11;
		mas[i][M - 2] = 11;
		mas[i][M - 3] = 11;
	}

	while (procedure_gen_mega_rand_with_rand_room_int(mas, number_rooms))
	{
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < M; j++)
			{
				mas[i][j] = 0;
			}
		}

		for (int i = 0; i < M; i++)
		{
			mas[0][i] = 11;
			mas[1][i] = 11;
			mas[2][i] = 11;

			mas[N - 1][i] = 11;
			mas[N - 2][i] = 11;
			mas[N - 3][i] = 11;
		}

		for (int i = 0; i < N; i++)
		{
			mas[i][0] = 11;
			mas[i][1] = 11;
			mas[i][2] = 11;

			mas[i][M - 1] = 11;
			mas[i][M - 2] = 11;
			mas[i][M - 3] = 11;
		}
	}

	delete_walls(mas);
}

int ALevelSpawner_V1::fun_long_room_int(std::vector<std::vector<int>>& mas, int lenght_room, int x, int y)
{

	int obr_add_x = 0;
	int obr_sub_x = 0;

	int obr_add_y = 0;
	int obr_sub_y = 0;

	if (obr_point_int(mas, x + 1, y) > 1)
	{
		obr_add_x++;
	}

	if (obr_point_int(mas, x - 1, y) > 1)
	{
		obr_sub_x++;
	}

	if (obr_point_int(mas, x, y + 1) > 1)
	{
		obr_add_y++;
	}

	if (obr_point_int(mas, x, y - 1) > 1)
	{
		obr_sub_y++;
	}

	for (int i = 2; i <= lenght_room; i++)
	{
		if (obr_point_int(mas, x + i, y) > 0)
		{
			obr_add_x++;
		}

		if (obr_point_int(mas, x - i, y) > 0)
		{
			obr_sub_x++;
		}

		if (obr_point_int(mas, x, y + i) > 0)
		{
			obr_add_y++;
		}

		if (obr_point_int(mas, x, y - i) > 0)
		{
			obr_sub_y++;
		}
	}

	if (obr_add_x > 0 && obr_add_y > 0 && obr_sub_y > 0 && obr_sub_y > 0)
	{
		return 1;
	}

	return 0;
}

int ALevelSpawner_V1::fun_fin_long_room_int(std::vector<std::vector<int>>& mas, int lenght_room, int x, int y, int vec_x, int vex_y)
{
	int obr_total = 0;

	if (obr_point_int(mas, x + vec_x, y + vex_y) == 1)
	{
		obr_total++;
	}

	for (int i = 2; i <= lenght_room; i++)
	{
		if (obr_point_int(mas, x + vec_x * i, y + vex_y * i) == 0)
		{
			obr_total++;
		}
	}

	for (int i = 1; i <= lenght_room; i++)
	{
		if (mas[y + vex_y * i][x + vec_x * i] == 0)
		{
			obr_total++;
		}
	}

	if (obr_total == (lenght_room * 2))
	{
		return 1;
	}

	return 0;
}

int ALevelSpawner_V1::change_data_int(std::vector<std::vector<int>>& mas, int lenght_room, int& x, int& y, int vec_x, int vec_y)
{
	for (int i = 1; i <= lenght_room; i++)
	{
		mas[y + vec_y * i][x + vec_x * i] = lenght_room;
	}

	x += vec_x * lenght_room;
	y += vec_y * lenght_room;

	return 0;
}

int ALevelSpawner_V1::obr_point_int(std::vector<std::vector<int>>& mas, int x, int y)
{
	int flag = 0;

	if (mas[y + 1][x] != 0)
	{
		flag++;
	}

	if (mas[y - 1][x] != 0)
	{
		flag++;
	}

	if (mas[y][x + 1] != 0)
	{
		flag++;
	}

	if (mas[y][x - 1] != 0)
	{
		flag++;
	}

	return flag;
}

void ALevelSpawner_V1::delete_walls(std::vector<std::vector<int>>& mas)
{
	for (int i = 0; i < mas.size(); i++)
	{
		for (int j = 0; j < mas[i].size(); j++)
		{
			if (mas[i][j] == 11)
			{
				mas[i][j] = 0;
			}
		}
	}
}

/*void ALevelSpawner_V1::DrawRoomCreationMassage(bool Check, FString RoomName)
{
	//Check ? GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Cyan, "Room " + RoomName + " spawned successfully") :
		//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "Room spawn with path " + RoomName + " failed");
	//UE_LOG(LogTemp, Display, TEXT("%s"), *a);
	//Check ? UE_LOG(LogTemp, Display, TEXT("Room spawned successfully with path %s"), *RoomName) : UE_LOG(LogTemp, Warning, TEXT("Room spawn with path %s failed"), *RoomName);
	if (Check)
	{
		UE_LOG(LogTemp, Display, TEXT("Room spawned successfully with path %s"), *RoomName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Room spawn with path %s failed"), *RoomName);
	}
}*/

void ALevelSpawner_V1::SpawnRoom(UWorld* world, FString RoomName, FVector RoomVector, FRotator RoomRotator, int UniqueIndex)
{
	bool RoomSpawnedSuccess = false;
	FString a;
	a.AppendInt(CounterToSpawn);

	ULevelStreamingDynamic::LoadLevelInstance(world, *RoomName, RoomVector, RoomRotator, RoomSpawnedSuccess, a);
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
			Cell2RoomVector = FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize, 0);
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
			Cell2RoomVector = FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize, 0);
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
			Cell2RoomVector = FVector(IndexY * LevelsGridSize, IndexX * LevelsGridSize + LevelsGridSize / 2, 0);
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
			Cell2RoomVector = FVector(IndexY * LevelsGridSize, IndexX * LevelsGridSize - LevelsGridSize / 2, 0);
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
				//Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0));
				Cell4RoomVector = FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0);
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
				//Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0));
				Cell4RoomVector = FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0);
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
				//Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0));
				Cell4RoomVector = FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0);
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
				//Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0));
				Cell4RoomVector = FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0);
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
				//Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0));
				Cell4RoomVector = FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0);
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
				//Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0));
				Cell4RoomVector = FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize + LevelsGridSize / 2, 0);
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
				//Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0));
				Cell4RoomVector = FVector(IndexY * LevelsGridSize + LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0);
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
				//Cell4RoomVector.AddBounded(FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0));
				Cell4RoomVector = FVector(IndexY * LevelsGridSize - LevelsGridSize / 2, IndexX * LevelsGridSize - LevelsGridSize / 2, 0);
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

void ALevelSpawner_V1::PrintMap(std::vector<std::vector<int>>& mas)
{
	for (size_t i = 0; i < mas.size(); i++)
	{
		FString a;
		for (size_t j = 0; j < mas[0].size(); j++)
		{
			a.AppendInt(mas[i][j]);
		}
		UE_LOG(LogTemp, Display, TEXT("%s"), *a);
	}
}

// Called when the game starts or when spawned
void ALevelSpawner_V1::BeginPlay()
{
	Super::BeginPlay();
	if (NumberOfBeginRooms < 1 || NumberOf1CellRooms < 1 || NumberOf2CellRooms < 1 || NumberOfEndRooms < 1 || NumberOf4CellRooms < 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Yellow, "BEGINPLAY CALLED SEVERAL TIMES, SOME OF THE UPROPERTIES EQUALS 0");
		return;
	}
	UWorld* World = GetWorld();
	if (World) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "World found");
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, "World not found");
		return;
	}

	UGameInstanceToSave* const TempGameInstance = World != nullptr ? World->GetGameInstance<UGameInstanceToSave>() : nullptr;
	if (TempGameInstance) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "GameInstance found");
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, "GameInstance not found");
		return;
	}
	FGenericPlatformMath::RandInit(TempGameInstance->Seed);

	FString Temp = "Generated Seed: ";
	Temp.AppendInt(TempGameInstance->Seed);
	GEngine->AddOnScreenDebugMessage(-1, INFINITY, FColor::Emerald, Temp);

	for (size_t i = 0; i < MatrixVerticalSize; i++)
	{
		std::vector<int> Temp_Mat;
		for (size_t j = 0; j < MatrixHorizontalSize; j++)
		{
			Temp_Mat.push_back(0);
		}
		matrix.push_back(Temp_Mat);
	}
	
	Generation_Map_Test1_int(matrix, NumberOfRoomsToSpawn - 1);

	PrintMap(matrix);

	for (size_t i = 0; i < matrix.size(); i++)
		for (size_t j = 0; j < matrix[0].size(); j++)
			if (matrix[i][j] == 8)
			{
				RecursivePath(0, 0, i, j, World);
				goto end_loop;
			}
end_loop:;
}

// Called every frame
void ALevelSpawner_V1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

