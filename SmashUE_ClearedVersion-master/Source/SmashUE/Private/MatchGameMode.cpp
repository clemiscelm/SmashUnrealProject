// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchGameMode.h"

#include "Editor.h"
#include "Arena/ArenaPlayerStart.h"
#include "Kismet/GameplayStatics.h"

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
	for(AArenaPlayerStart* PlayerStartsPoint : PlayerStartsPoints)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, PlayerStartsPoint->GetFName().ToString());
	}
}

