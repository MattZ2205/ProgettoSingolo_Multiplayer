// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PowerUpTaker.h"
#include "GP3_MultiplayerGameMode.generated.h"

UCLASS(minimalapi)
class AGP3_MultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGP3_MultiplayerGameMode();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	TSubclassOf<APowerUpTaker> PowerUpTakerClass;

private:
	UPROPERTY(EditAnywhere, Category = "PowerUp")
	FVector SpawnLocation;
};