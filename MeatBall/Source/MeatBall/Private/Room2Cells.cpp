// Copyright 2021, Aks, Spirt


#include "Room2Cells.h"

Room2Cells::Room2Cells(
	unsigned short int Up,
	unsigned short int UpRight,
	unsigned short int DownRight,
	unsigned short int Down,
	unsigned short int DownLeft,
	unsigned short int UpLeft)
{
	this->Up = Up;
	this->UpRight = UpRight;
	this->DownRight = DownRight;
	this->Down = Down;
	this->DownLeft = DownLeft;
	this->UpLeft = UpLeft;
}

FString Room2Cells::GenerateRoomName(int NumberOf2CellRooms)
{
	FString ReturningName = "/Game/Levels/2Cells/";

	FString TempCode;
	TempCode.AppendInt(Up);
	TempCode.AppendInt(UpRight);
	TempCode.AppendInt(DownRight);
	TempCode.AppendInt(Down);
	TempCode.AppendInt(DownLeft);
	TempCode.AppendInt(UpLeft);

	ReturningName.Append(TempCode + "_Variations/");

	FString TempName = "Room_2_" + TempCode + "_";

	TempName.AppendInt(FGenericPlatformMath::Rand() % NumberOf2CellRooms);

	return ReturningName.Append(TempName + "." + TempName);
}

Room2Cells::~Room2Cells()
{
}
