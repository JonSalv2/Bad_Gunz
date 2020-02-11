// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BadGunzGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BADGUNZ_API ABadGunzGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		virtual void StartPlay() override;
	
};
