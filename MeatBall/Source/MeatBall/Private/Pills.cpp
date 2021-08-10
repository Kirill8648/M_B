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
	
	for (int i = 0; i < hero->pills_characteristic.number_repetitions; i++)
	{
		interaction_with_hero(hero);
	}
}

void APills::interaction_with_hero(ARoguelike_hero* hero)
{

	FStruct_pill temp_global_struct_pill=feature_pill;

	if(hero->pills_characteristic.only_size!=0)
	{
		switch (hero->pills_characteristic.only_size+1)
		{
		case Gigantic:
			temp_global_struct_pill.size_pill = Gigantic;
			break;
		case Big:
			temp_global_struct_pill.size_pill = Big;
			break;
		case Normal:
			temp_global_struct_pill.size_pill = Normal;
			break;
		case Small:
			temp_global_struct_pill.size_pill = Small;
			break;
		case Tiny:
			temp_global_struct_pill.size_pill = Tiny;
			break;
		default:
			break;
		}
	}

	if(hero->pills_characteristic.all_pill_good)
	{
		temp_global_struct_pill.usefulness=Good;
	}
	if (hero->pills_characteristic.all_pill_bad)
	{
		temp_global_struct_pill.usefulness=Bad;
	}

	
	if(hero->pills_characteristic.random_pill_bad_or_good)
	{
		switch (FGenericPlatformMath::Rand() % 1)
		{
			case 0:
				temp_global_struct_pill.usefulness=Good;
				break;
			default:
				temp_global_struct_pill.usefulness=Bad;
				break;
		}
	}


	
	
	float size_multiplier = 1;

	/*if(hero->pills_characteristic.only_size!=0)
	{
		switch (hero->pills_characteristic.only_size+1)
		{
			case Gigantic:
				size_multiplier = 2;
				break;
		case Big:
			size_multiplier = 1.5f;
			break;
		case Normal:
			size_multiplier = 1;
			break;
		case Small:
			size_multiplier = 0.75f;
			break;
		case Tiny:
			size_multiplier = 0.5f;
			break;
		default:
			break;
		}
	}*/
//	else
	//{	
		if (temp_global_struct_pill.size_pill == Gigantic) size_multiplier = 2;
		else if (temp_global_struct_pill.size_pill == Big) size_multiplier = 1.5f;
		else if (temp_global_struct_pill.size_pill == Normal) size_multiplier = 1;
		else if (temp_global_struct_pill.size_pill == Small) size_multiplier = 0.75;
		else if (temp_global_struct_pill.size_pill == Tiny) size_multiplier = 0.5;
	//}

	switch (temp_global_struct_pill.type_pill)
	{
	case Speed:
		if (temp_global_struct_pill.usefulness == Bad)
			hero->GetCharacterMovement()->MaxWalkSpeed -= 300 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.speed_multiplier * hero->
				pills_characteristic.Bad_multiplier;
		else if (temp_global_struct_pill.usefulness == Good)
			hero->GetCharacterMovement()->MaxWalkSpeed += 300 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.speed_multiplier * hero->
				pills_characteristic.Good_multiplier;
		break;
	case Air_control:
		if (temp_global_struct_pill.usefulness == Bad)
			hero->GetCharacterMovement()->AirControl -= 1 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.air_control_multiplier * hero->
				pills_characteristic.Bad_multiplier;
		else if (temp_global_struct_pill.usefulness == Good)
			hero->GetCharacterMovement()->AirControl += 1 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.air_control_multiplier * hero->
				pills_characteristic.Good_multiplier;
		break;
	case Jump_height:
		if (temp_global_struct_pill.usefulness == Bad)
			hero->GetCharacterMovement()->JumpZVelocity -= 300 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.jump_height_multiplier * hero->
				pills_characteristic.Bad_multiplier;
		else if (temp_global_struct_pill.usefulness == Good)
			hero->GetCharacterMovement()->JumpZVelocity += 300 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.jump_height_multiplier * hero->
				pills_characteristic.Good_multiplier;
		break;
	case Experimental:
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("SIZE= %i"),feature_pill.size_pill));

		for (int i = 0; i < hero->pills_characteristic.number_experimental_repetitions; i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("FOR")));

			FStruct_pill temp_struct_pill;

			const TArray<FName> NameArr = PillDataTable->GetRowNames();
			temp_struct_pill = *PillDataTable->FindRow<FStruct_pill>(NameArr[FGenericPlatformMath::Rand() % NumberOfRows], Temp_string, true);

			while (temp_struct_pill.type_pill == Experimental)
			{
				GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("Exsper")));
				temp_struct_pill = *PillDataTable->FindRow<FStruct_pill>(NameArr[FGenericPlatformMath::Rand() % NumberOfRows], Temp_string, true);
			}

			switch (temp_struct_pill.type_pill)
			{
			case Speed:
				GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("+Speed")));
				if (temp_struct_pill.usefulness == Bad)
					hero->GetCharacterMovement()->MaxWalkSpeed -= 300 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.speed_multiplier * hero->
						pills_characteristic.Bad_multiplier;
				else if (temp_struct_pill.usefulness == Good)
					hero->GetCharacterMovement()->MaxWalkSpeed += 300 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.speed_multiplier * hero->
						pills_characteristic.Good_multiplier;
				break;
			case Air_control:
				GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("+Air")));
				if (temp_struct_pill.usefulness == Bad)
					hero->GetCharacterMovement()->AirControl -= 1 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.air_control_multiplier * hero->
						pills_characteristic.Bad_multiplier;
				else if (temp_struct_pill.usefulness == Good)
					hero->GetCharacterMovement()->AirControl += 1 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.air_control_multiplier * hero->
						pills_characteristic.Good_multiplier;
				break;
			case Jump_height:
				GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("+Jump")));
				if (temp_struct_pill.usefulness == Bad)
					hero->GetCharacterMovement()->JumpZVelocity -= 300 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.jump_height_multiplier * hero->
						pills_characteristic.Bad_multiplier;
				else if (temp_struct_pill.usefulness == Good)
					hero->GetCharacterMovement()->JumpZVelocity += 300 * size_multiplier * hero->pills_characteristic.general_multiplier * hero->pills_characteristic.jump_height_multiplier * hero->
						pills_characteristic.Good_multiplier;
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
	return PillDataTable->FindRow<FStruct_pill>(NameArr[number_in_table], Temp_string, true);
}


//void print_data_pill(APills& pill)
//{
//	UE_LOG(LogTemp, Display, TEXT("%s"),pill.name);
//}
