// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpTaker.generated.h"

UCLASS()
class GP3_MULTIPLAYER_API APowerUpTaker : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class UPowerUp* PowerUpComponent;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

public:
	APowerUpTaker();

private:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
