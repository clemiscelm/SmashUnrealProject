﻿	// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashCharacter.h"
#include "SmashUE/Public/Character/States/SmashCharacterStateMachine.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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
	TickStateMachine(DeltaTime);
	RotateMeshUsingOrientX();
}

// Called to bind functionality to input
void ASmashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetupMappingContextIntoController();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent == nullptr) return;
	BindInputMoveXAxisAndActions(EnhancedInputComponent);
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

void ASmashCharacter::TickStateMachine(float DeltaTime) const
{
	if(StateMachine == nullptr) return;
	StateMachine->Tick(DeltaTime);
}

void ASmashCharacter::ChangeAnimation(UAnimMontage* Montage) 
{
	if(Montage == nullptr) return;
	this->PlayAnimMontage(Montage);
}

void ASmashCharacter::SetupMappingContextIntoController() const
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController == nullptr) return;
	ULocalPlayer* Player = PlayerController->GetLocalPlayer();
	if(Player == nullptr) return;
	UEnhancedInputLocalPlayerSubsystem* InputSystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if(InputSystem == nullptr) return;
	InputSystem->AddMappingContext(InputMappingContext,0);
	
}

float ASmashCharacter::GetInputMoveX()
{
	return InputMoveX; 
}
void ASmashCharacter::BindInputMoveXAxisAndActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	if(InputData == nullptr) return;
	if(InputData->InputActionMoveX)
	{
		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveX,
			ETriggerEvent::Started,
			this,
			&ASmashCharacter::OnInputMoveX);
		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveX,
			ETriggerEvent::Triggered,
			this,
			&ASmashCharacter::OnInputMoveX);
	}
}


void ASmashCharacter::OnInputMoveX(const FInputActionValue& InputActionValue)
{
	InputMoveX = InputActionValue.Get<float>();
}






