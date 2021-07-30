// Copyright 2021, Aks, Spirt


#include "RoomBaseLevelScriptActor.h"


ARoomBaseLevelScriptActor::ARoomBaseLevelScriptActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SplineShit = CreateDefaultSubobject<USplineComponent>("Spline");
	if (SplineShit) SetRootComponent(SplineShit);
}
