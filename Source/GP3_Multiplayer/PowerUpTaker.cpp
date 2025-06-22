// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpTaker.h"
#include "Components/BoxComponent.h"
#include "PowerUp.h"

// Sets default values
APowerUpTaker::APowerUpTaker()
{
	bReplicates = true;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	PowerUpComponent = CreateDefaultSubobject<UPowerUp>(TEXT("PowerUpComponent"));

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerUpTaker::OnBoxBeginOverlap);
}

void APowerUpTaker::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		PowerUpComponent->ActivatePowerUp();
		Destroy();
	}
}