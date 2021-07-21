// Copyright 2021, Aks, Spirt


#include "GameInstanceToSave.h"

UGameInstanceToSave::UGameInstanceToSave()
{
	//-------------TEST--------------
	this->Seed = FMath::RandRange(100000000, 999999999);

	//Seed = 522492128;
	//FGenericPlatformMath::RandInit(this->Seed);
	//-------------------------------
}