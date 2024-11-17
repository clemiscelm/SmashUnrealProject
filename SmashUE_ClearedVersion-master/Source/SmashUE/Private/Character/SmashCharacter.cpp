﻿	// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashCharacter.h"

#include "SmashUE/Public/Character/States/SmashCharacterStateMachine.h"

	// Sets default values
ASmashCharacter::ASmashCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASmashCharacter::BeginPlay()
{
	Super::BeginPlay();
	CreateMachine();
	InitStatMachine();
	
}

// Called every frame
void ASmashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateMeshUsingOrientX();
}

// Called to bind functionality to input
void ASmashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ASmashCharacter::GetOrientX() const
{
	return OrientX;
}
void ASmashCharacter::SetOrientX(float NewOrientX)
{
	OrientX = NewOrientX;
	
}

void ASmashCharacter::RotateMeshUsingOrientX() const
{
	FRotator Rotation = GetMesh()->GetRelativeRotation();
	Rotation.Yaw = -90.f * OrientX;
	GetMesh()->SetRelativeRotation(Rotation);
}


void ASmashCharacter::InitStatMachine()
{
	if(StateMachine == nullptr) return;
	StateMachine->Init(this);
}

void ASmashCharacter::CreateMachine()
{
	StateMachine = NewObject<USmashCharacterStateMachine>(this);
}


