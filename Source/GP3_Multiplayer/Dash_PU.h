// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "Dash_PU.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class GP3_MULTIPLAYER_API UDash_PU : public UPowerUp
{
	GENERATED_BODY()

public:
	void ActivatePowerUp() override;
};
