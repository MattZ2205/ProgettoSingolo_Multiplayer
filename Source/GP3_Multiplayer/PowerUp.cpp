// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "Kismet/GameplayStatics.h"
#include "GP3_MultiplayerCharacter.h"

// Sets default values for this component's properties
UPowerUp::UPowerUp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPowerUp::ActivatePowerUp_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Preso il PowerUp");

	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGP3_MultiplayerCharacter::StaticClass(), FoundPlayers);

	for (int i = 0; i < FoundPlayers.Num(); i++)
	{
		Cast<AGP3_MultiplayerCharacter>(FoundPlayers[i])->AddPUToPlayer();
	}
}