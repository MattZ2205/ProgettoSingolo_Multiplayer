// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerUp.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP3_MULTIPLAYER_API UPowerUp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerUp();
	UFUNCTION(NetMulticast, Reliable)
	virtual void ActivatePowerUp();
};
