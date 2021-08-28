// Copyright 2021, Aks, Spirt


#include "GameInstanceToSave.h"

UGameInstanceToSave::UGameInstanceToSave()
{
	//-------------TODO--------------
	/*this->Seed = FMath::RandRange(100000000, 999999999);
	FGenericPlatformMath::RandInit(this->Seed);
	FGenericPlatformMath::SRandInit(this->Seed);*/
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, INFINITY, FColor::Emerald,
		                                 FString::Printf(TEXT("Generated seed: %d"), this->Seed));*/
	//-------------------------------

	//Seed = 522492128;
	//FGenericPlatformMath::RandInit(this->Seed);
	//-------------------------------
}

void UGameInstanceToSave::RandomizeSeed()
{
	this->Seed = FMath::RandRange(100000000, 999999999);
}

void UGameInstanceToSave::InitializeRandomGeneratorsBySeed() const
{
	if (this->Seed != NULL)
	{
		FGenericPlatformMath::RandInit(this->Seed);
		FGenericPlatformMath::SRandInit(this->Seed);
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red,
			                                 FString::Printf(TEXT("TRYING TO INITIALIZE RANDOMS WITH NULL SEED, RANDOMS DOES NOT INITIALIZED!")));
	}
}
