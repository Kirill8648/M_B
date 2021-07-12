// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"
#include "RoomBase.h"

/**
 * 
 */
class MEATBALL_API Room2Cells : public RoomBase
{
private:
	unsigned short int Up;
	unsigned short int UpRight;
	unsigned short int DownRight;
	unsigned short int Down;
	unsigned short int DownLeft;
	unsigned short int UpLeft;

public:
	Room2Cells(unsigned short int Up,
		unsigned short int UpRight,
		unsigned short int DownRight,
		unsigned short int Down,
		unsigned short int DownLeft,
		unsigned short int UpLeft);
	FString GenerateRoomName(int);
	~Room2Cells();
};
