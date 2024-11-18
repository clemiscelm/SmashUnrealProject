// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/SmashCharacterStateWalk.h"
#include "Animation/AnimMontage.h"
#include "Character/SmashCharacter.h"


ESmashCharacterStateID USmashCharacterStateWalk::GetStateID()
{
	return ESmashCharacterStateID::Walk;
}



void USmashCharacterStateWalk::StateEnter(ESmashCharacterStateID PreviousStateID)
{

	Super::StateEnter(PreviousStateID);
	FVector ForwardVector = FVector(Character->GetOrientX(),0,0);
	FVector NewLocation = Character->GetActorLocation() + (ForwardVector * MoveSpeedMax);
	Character->SetActorLocation(NewLocation);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Enter StateWalk"));
}


void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Exit StateWalk"));
}

void USmashCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, TEXT("Tick StateWalk"));
}
