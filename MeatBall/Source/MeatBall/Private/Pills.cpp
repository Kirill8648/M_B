// Copyright 2021, Aks, Spirt


#include "Pills.h"

// Sets default values
APills::APills()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> Table_helper(TEXT("DataTable'/Game/Data/Pills_Data_Table.Pills_Data_Table'"));
	if (Table_helper.Succeeded())
	{
		PillDataTable = Table_helper.Object;
	}

	set_actor_struct_pill();
}

// Called when the game starts or when spawned
void APills::BeginPlay()
{
	Super::BeginPlay();
	
	set_actor_struct_pill();
}

// Called every frame
void APills::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APills::app_stat_pills(ARoguelike_hero* hero)
{
	print_struct_pill();
	for (int i=0; i<1;i++)
	{
	interaction_with_hero(hero);
	}
}

void APills::interaction_with_hero(ARoguelike_hero* hero)
{
	float multiplier = 1;

	if (feature_pill.size_pill == Gigantic) multiplier = 2;
	else if (feature_pill.size_pill == Big) multiplier = 1.5f;
	else if (feature_pill.size_pill == Normal) multiplier = 1;
	else if (feature_pill.size_pill == Small) multiplier = 0.75;
	else if (feature_pill.size_pill == Tiny) multiplier = 0.5;

	switch (feature_pill.type_pill)
	{
	case Speed:
		if (feature_pill.usefulness == Bad)
		hero->GetCharacterMovement()->MaxWalkSpeed -= 300 * multiplier;
		else if (feature_pill.usefulness == Good)
			hero->GetCharacterMovement()->MaxWalkSpeed += 300 * multiplier;
		break;
	case Air_control:
		if (feature_pill.usefulness == Bad)
			hero->GetCharacterMovement()->AirControl -= 1 * multiplier;
		else if (feature_pill.usefulness == Good)
			hero->GetCharacterMovement()->AirControl += 1 * multiplier;
		break;
	case Jump_height:
		if (feature_pill.usefulness == Bad)
			hero->GetCharacterMovement()->JumpZVelocity -= 300 * multiplier;
		else if(feature_pill.usefulness == Good)
			hero->GetCharacterMovement()->JumpZVelocity += 300 * multiplier;
		break;
	case Experimental:
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("SIZE= %i"),feature_pill.size_pill));

		for (int i = 0; i < 3; i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("FOR")));

			FStruct_pill temp_struct_pill;

			const TArray<FName> NameArr = PillDataTable->GetRowNames();
			int temp_num_in_table = FGenericPlatformMath::Rand() % NumberOfRows; //

			//static const FString ContextString(TEXT(""));
			temp_struct_pill = *PillDataTable->FindRow<FStruct_pill>(NameArr[temp_num_in_table], Temp_string, true);

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("TYPE:%i USEFUL:%i SIZE:%i %i"),temp_struct_pill.type_pill,temp_struct_pill.usefulness,temp_struct_pill.size_pill,temp_struct_pill.size_pill));

			while(temp_struct_pill.type_pill==Experimental)
			{
				GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("Exsper")));

				temp_num_in_table=FGenericPlatformMath::Rand() % NumberOfRows;//
				temp_struct_pill =*PillDataTable->FindRow<FStruct_pill>(NameArr[temp_num_in_table], Temp_string, true);	 
			}

			switch (temp_struct_pill.type_pill)
			{
			case Speed: GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("+Speed")));
				if (temp_struct_pill.usefulness == Bad)
					hero->GetCharacterMovement()->MaxWalkSpeed -= 300 * multiplier;
				else if (temp_struct_pill.usefulness == Good)
					hero->GetCharacterMovement()->MaxWalkSpeed += 300 * multiplier;
				break;
			case Air_control: GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("+Air")));
				if (temp_struct_pill.usefulness == Bad)
					hero->GetCharacterMovement()->AirControl -= 1 * multiplier;
				else if (temp_struct_pill.usefulness == Good)
					hero->GetCharacterMovement()->AirControl += 1 * multiplier;
				break;
			case Jump_height: GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("+Jump")));
				if (temp_struct_pill.usefulness == Bad)
					hero->GetCharacterMovement()->JumpZVelocity -= 300 * multiplier;
				else if (temp_struct_pill.usefulness == Good)
					hero->GetCharacterMovement()->JumpZVelocity += 300 * multiplier;
				break;
			default:
				GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("+Exsper")));
				break;
			}
		}

		break;
	default: break;
	}
}

void APills::set_actor_struct_pill()
{
	const TArray<FName> NameArr = PillDataTable->GetRowNames();
	NumberOfRows = NameArr.Num() - 1;

	if (random_pill)
	{
		num_pill_in_table = FGenericPlatformMath::Rand() % NumberOfRows;
	}

	if (num_pill_in_table > NumberOfRows - 1 || num_pill_in_table < 0)
	{
		num_pill_in_table = 0;
	}

	name = NameArr[num_pill_in_table];

	FStruct_pill* TempBeginStruct = PillDataTable->FindRow<FStruct_pill>(name, Temp_string, true);

	feature_pill = *TempBeginStruct;
}

void APills::print_struct_pill()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
	                                 FString::Printf(TEXT("TYPE:%i USEFUL:%i SIZE:%i"), static_cast<int>(feature_pill.type_pill), static_cast<int>(feature_pill.usefulness),
                                                 static_cast<int>(feature_pill.size_pill)));
}


FStruct_pill* APills::get_struct_pill_from_table(int number_in_table)
{
	const TArray<FName> NameArr = PillDataTable->GetRowNames();
	//static const FString ContextString(TEXT(""));
	return PillDataTable->FindRow<FStruct_pill>(NameArr[number_in_table], Temp_string, true);
}


//void print_data_pill(APills& pill)
//{
//	UE_LOG(LogTemp, Display, TEXT("%s"),pill.name);
//}
