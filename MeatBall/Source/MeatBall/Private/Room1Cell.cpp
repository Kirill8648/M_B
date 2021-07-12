// Copyright 2021, Aks, Spirt


#include "Room1Cell.h"

Room1Cell::Room1Cell(
	unsigned short int Up,
	unsigned short int Right,
	unsigned short int Down,
	unsigned short int Left)
{
	this->Up = Up;
	this->Right = Right;
	this->Down = Down;
	this->Left = Left;
}

FString Room1Cell::GenerateRoomName(int NumberOf1CellRooms)
{
	FString ReturningName = "/Game/Levels/1Cells/";

	FString TempCode;
	TempCode.AppendInt(Up);
	TempCode.AppendInt(Right);
	TempCode.AppendInt(Down);
	TempCode.AppendInt(Left);

	ReturningName.Append(TempCode + "_Variations/");

	FString TempName = "Room_1_" + TempCode + "_";
	TempName.AppendInt(FGenericPlatformMath::Rand() % NumberOf1CellRooms);

	return ReturningName.Append(TempName + "." + TempName);
}

Room1Cell::~Room1Cell()
{
}
