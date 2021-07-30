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
private:
	UGameInstanceToSave();

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Seed;
};
