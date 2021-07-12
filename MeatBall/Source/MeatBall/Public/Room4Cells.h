// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"
#include "RoomBase.h"

/**
 * 
 */
class MEATBALL_API Room4Cells : public RoomBase
{
private:
	unsigned short int UpLeft;
	unsigned short int UpRight;
	unsigned short int RightUp;
	unsigned short int RightDown;
	unsigned short int DownRight;
	unsigned short int DownLeft;
	unsigned short int LeftDown;
	unsigned short int LeftUp;

public:
	Room4Cells(unsigned short int UpLeft,
		unsigned short int UpRight,
		unsigned short int RightUp,
		unsigned short int RightDown,
		unsigned short int DownRight,
		unsigned short int DownLeft,
		unsigned short int LeftDown,
		unsigned short int LeftUp);
	FString GenerateRoomName(int);
	~Room4Cells();
};
