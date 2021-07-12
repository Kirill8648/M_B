// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"
#include "RoomBase.h"

/**
 * 
 */
class MEATBALL_API Room1Cell : public RoomBase
{
private:
	unsigned short int Up;
	unsigned short int Right;
	unsigned short int Down;
	unsigned short int Left;

public:
	Room1Cell(unsigned short int Up,
		unsigned short int Right,
		unsigned short int Down,
		unsigned short int Left);
	FString GenerateRoomName(int);
	~Room1Cell();
};
