﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterStateMachine.h"
#include "Character/States/SmashCharacterState.h"
#include "Character/SmashCharacter.h"


void USmashCharacterStateMachine::Init(ASmashCharacter* InCharacter)
{
	Character = InCharacter;
	FindStates();
	InitStates();
	ChangeState(ESmashCharacterStateID::Idle);
}

ASmashCharacter* USmashCharacterStateMachine::GetCharacter() const
{
	return Character;
}
void USmashCharacterStateMachine::FindStates()
{
	TArray<UActorComponent*> FoundComponents = Character->K2_GetComponentsByClass(USmashCharacterState::StaticClass());
	for (UActorComponent* StateComponent : FoundComponents)
	{
		USmashCharacterState* State = Cast<USmashCharacterState>(StateComponent);
		if (State == nullptr)continue;
		if(State->GetStateID() == ESmashCharacterStateID::None) continue;
		
		AllStates.Add(State);
		
	}
}

void USmashCharacterStateMachine::InitStates()
{
	for (USmashCharacterState* State : AllStates)
	{
		State->StateInit(this);
	}
	
}

USmashCharacterState* USmashCharacterStateMachine::GetState(ESmashCharacterStateID StateID)
{
	for (USmashCharacterState* State : AllStates)
	{
		if(State->GetStateID() == StateID)
		{
			return State;
		}
	}
	return nullptr;
}

void USmashCharacterStateMachine::ChangeState(ESmashCharacterStateID NexStateID)
{
	USmashCharacterState* NewState = GetState(NexStateID);
	if(NewState == nullptr) return;
	if(CurrentState != nullptr)
	{
		CurrentState->StateExit(NexStateID);
	}
	ESmashCharacterStateID PreviuosStateID = CurrentStateID;
	CurrentStateID = NexStateID;
	CurrentState = NewState;
	if(CurrentState != nullptr)
	{
		CurrentState->StateEnter(PreviuosStateID);
	}
}


