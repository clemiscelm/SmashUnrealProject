// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MatchGameMode.h"

#include "Editor.h"
#include "Arena/ArenaPlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SmashCharacter.h"
#include "Arena/ArenaSettings.h"
#include "Character/SmashCharacterSettings.h"

void AMatchGameMode::FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultActors)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArenaPlayerStart::StaticClass(), FoundActors);
	for(int i = 0; i < FoundActors.Num();++i)
	{
		AArenaPlayerStart* ArenaPlayerStartActor = Cast<AArenaPlayerStart>(FoundActors[i]);
		if(ArenaPlayerStartActor == nullptr) continue;
		ResultActors.Add(ArenaPlayerStartActor);
	}
}

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AArenaPlayerStart*> PlayerStartsPoints;
	FindPlayerStartActorsInArena(PlayerStartsPoints);
	SpawnCharacters(PlayerStartsPoints);
	for(AArenaPlayerStart* PlayerStartsPoint : PlayerStartsPoints)
	{
		EAutoReceiveInput::Type InputeType = PlayerStartsPoint->AutoReceiveInput.GetValue();
		TSubclassOf<ASmashCharacter> SmashCharacterClass = GetSmashCharacterClassFromInputType(InputeType);
		if(SmashCharacterClass == nullptr) continue;
		
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, SmashCharacterClass->GetFName().ToString());
	}
}

TSubclassOf<ASmashCharacter> AMatchGameMode::GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const
{
	const UArenaSettings* ArenaSettings = GetDefault<UArenaSettings>();
	switch (InputType)
	{
	case EAutoReceiveInput::Player0:
		return ArenaSettings->SmashCharacterClassP0;
	case EAutoReceiveInput::Player1:
		return ArenaSettings->SmashCharacterClassP1;
	case EAutoReceiveInput::Player2:
		return ArenaSettings->SmashCharacterClassP2;
	case EAutoReceiveInput::Player3:
		return ArenaSettings->SmashCharacterClassP3;
	default:
		return nullptr;
	}
}

void AMatchGameMode::SpawnCharacters(const TArray<AArenaPlayerStart*>& SpawnPoints)
{
	for(AArenaPlayerStart* SpawnPoint : SpawnPoints)
	{
		EAutoReceiveInput::Type InputType = SpawnPoint->AutoReceiveInput.GetValue();
		TSubclassOf<ASmashCharacter> SmashCharacterClass = GetSmashCharacterClassFromInputType(InputType);
		if (SmashCharacterClass == nullptr) continue;
		ASmashCharacter* SmashCharacter = GetWorld()->SpawnActor<ASmashCharacter>(SmashCharacterClass, SpawnPoint->GetTransform());
		if(SmashCharacter == nullptr) continue;

		SmashCharacter->AutoPossessPlayer = SpawnPoint->AutoReceiveInput;
		SmashCharacter->SetOrientX(SpawnPoint->GetStartOrientX());
		//SmashCharacter->FinishSpawning(SpawnPoint->GetTransform());
		CharactersInsideArena.Add(SmashCharacter);
	}
}

USmashCharacterInputData* AMatchGameMode::LoadInputDataFromConfig()
{
	const USmashCharacterSettings* CharacterSettings = GetDefault<USmashCharacterSettings>();
	if(CharacterSettings == nullptr) return nullptr;
	return CharacterSettings->InputData.LoadSynchronous();
}

UInputMappingContext* AMatchGameMode::LoadInputMappingContextFromConfig()
{
	const USmashCharacterSettings* CharacterSettings = GetDefault<USmashCharacterSettings>();
	if(CharacterSettings == nullptr) return nullptr;
	return CharacterSettings->InputMappingContext.LoadSynchronous();
}
