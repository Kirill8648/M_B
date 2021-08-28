// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceToSave.generated.h"

/**
 *
 */
UCLASS()
class MEATBALL_API UGameInstanceToSave : public UGameInstance
{
	GENERATED_BODY()
	
	UGameInstanceToSave();

public:
	UPROPERTY(BlueprintReadWrite)
	int32 Seed = 0;

	UFUNCTION(BlueprintCallable)
	void RandomizeSeed();

	UFUNCTION(BlueprintCallable)
	void InitializeRandomGeneratorsBySeed() const;
};
