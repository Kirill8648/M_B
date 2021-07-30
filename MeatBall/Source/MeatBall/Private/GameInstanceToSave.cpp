// Copyright 2021, Aks, Spirt


#include "GameInstanceToSave.h"

UGameInstanceToSave::UGameInstanceToSave()
{
	//-------------TODO--------------
	this->Seed = FMath::RandRange(100000000, 999999999);
	FGenericPlatformMath::RandInit(this->Seed);
	FGenericPlatformMath::SRandInit(this->Seed);
	//GEngine->AddOnScreenDebugMessage(-1, INFINITY, FColor::Emerald,
	                                 //FString::Printf(TEXT("Generated seed: %d"), this->Seed));
	//-------------------------------

	//Seed = 522492128;
	//FGenericPlatformMath::RandInit(this->Seed);
	//-------------------------------
}
