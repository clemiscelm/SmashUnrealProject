﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedPlayerInput.h"
#include "SmashCharacterInputData.h"
#include "UObject/Object.h"
#include "SmashCharacterSettings.generated.h"

/**
 * 
 */
//class UInputMappingContext;
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName = "Smash Character Settings"))
class SMASHUE_API USmashCharacterSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "Input")
	TSoftObjectPtr<USmashCharacterInputData> InputData;
	UPROPERTY(Config, EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;
};
