// Copyright 2021, Aks, Spirt


#include "Room4Cells.h"

Room4Cells::Room4Cells(
	unsigned short int UpLeft,
	unsigned short int UpRight,
	unsigned short int RightUp,
	unsigned short int RightDown,
	unsigned short int DownRight,
	unsigned short int DownLeft,
	unsigned short int LeftDown,
	unsigned short int LeftUp)
{
	this->UpLeft = UpLeft;
	this->UpRight = UpRight;
	this->RightUp = RightUp;
	this->RightDown = RightDown;
	this->DownRight = DownRight;
	this->DownLeft = DownLeft;
	this->LeftDown = LeftDown;
	this->LeftUp = LeftUp;
}

FString Room4Cells::GenerateRoomName(int NumberOf4CellRooms)
{
	FString ReturningName = "/Game/Levels/4Cells/";

	FString TempCode;
	TempCode.AppendInt(UpLeft);
	TempCode.AppendInt(UpRight);
	TempCode.AppendInt(RightUp);
	TempCode.AppendInt(RightDown);
	TempCode.AppendInt(DownRight);
	TempCode.AppendInt(DownLeft);
	TempCode.AppendInt(LeftDown);
	TempCode.AppendInt(LeftUp);

	ReturningName.Append(TempCode + "_Variations/");

	FString TempName = "Room_4_" + TempCode + "_";
	TempName.AppendInt(FGenericPlatformMath::Rand() % NumberOf4CellRooms);
	
	return ReturningName.Append(TempName + "." + TempName);
}

Room4Cells::~Room4Cells()
{
}
