// Copyright 2021, Aks, Spirt

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Roguelike_hero.h"

#include "Pills.generated.h"

UENUM(BlueprintType)
enum EType_pill
{
	Speed UMETA(DisplayName = "Speed"),
	Air_control UMETA(DisplayName = "Air control"),
	Jump_height UMETA(DisplayName = "Jump height"),
	Experimental UMETA(DisplayName = " Experimental"),

	NGCT_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum EUsefulness_pill
{
	Good UMETA(DisplayName = "Good"),
	Bad UMETA(DisplayName = "Bad"),
	Neutral UMETA(DisplayName = "Neutral"),
	Specific UMETA(DisplayName = "Specific"),

	NNGCT_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum ESize_pill
{
	Gigantic UMETA(DisplayName = "Gigantic"),
	Big UMETA(DisplayName = "Big"),
	Normal UMETA(DisplayName = "Normal"),
	Small UMETA(DisplayName = "Small"),
	Tiny UMETA(DisplayName = "Tiny"),

	NNNGCT_Max UMETA(Hidden)
};


USTRUCT(BlueprintType)
struct FStruct_pill : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	TEnumAsByte<EType_pill> type_pill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	TEnumAsByte<EUsefulness_pill> usefulness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	TEnumAsByte<ESize_pill> size_pill;
};

UCLASS()
class MEATBALL_API APills : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APills();
	UFUNCTION(BlueprintCallable)
	void app_stat_pills(ARoguelike_hero* hero);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name = "???";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* PillDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStruct_pill feature_pill;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int num_pill_in_table = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool random_pill = false;


	int NumberOfRows;

	void interaction_with_hero(ARoguelike_hero* hero);

	void set_actor_struct_pill();
	FStruct_pill* get_struct_pill_from_table(int number_in_table);


	void print_struct_pill();


	 FString Temp_string="";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

//void print_data_pill(APills& pill);
