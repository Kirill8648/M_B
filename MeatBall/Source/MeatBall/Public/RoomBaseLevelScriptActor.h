// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "Engine/LevelScriptActor.h"
#include "Components/SplineComponent.h"
#include "RoomBaseLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class MEATBALL_API ARoomBaseLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	ARoomBaseLevelScriptActor();
public:
	UPROPERTY(BlueprintReadWrite)
	FSplinePoint StartSplinePoint;

	UPROPERTY(BlueprintReadWrite)
	FSplinePoint EndSplinePoint;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = "Spline")
	USplineComponent* SplineShit;
};
