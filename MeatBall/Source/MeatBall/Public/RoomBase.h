// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class MEATBALL_API RoomBase
{
public:
	RoomBase();
	virtual FString GenerateRoomName(int);
	virtual ~RoomBase();
};
