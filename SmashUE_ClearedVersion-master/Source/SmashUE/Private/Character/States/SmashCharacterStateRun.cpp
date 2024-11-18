// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/SmashCharacterStateRun.h"
#include "Animation/AnimMontage.h"
#include "Character/SmashCharacter.h"

ESmashCharacterStateID USmashCharacterStateRun::GetStateID()
{
	return ESmashCharacterStateID::Run;
}



void USmashCharacterStateRun::StateEnter(ESmashCharacterStateID PreviousStateID)
{

	Super::StateEnter(PreviousStateID);
	FVector ForwardVector = FVector(Character->GetOrientX(),0,0);
	FVector NewLocation = Character->GetActorLocation() + (ForwardVector * MoveSpeedMax);
	Character->SetActorLocation(NewLocation);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Enter StateRun"));
}


void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Exit StateRun"));
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, TEXT("Tick StateRun"));
}

