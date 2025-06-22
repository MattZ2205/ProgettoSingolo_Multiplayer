#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Door_PressurePlates.generated.h"

UCLASS()
class GP3_MULTIPLAYER_API ADoor_PressurePlates : public AActor
{
	GENERATED_BODY()

public:
	ADoor_PressurePlates();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Door")
	class UBoxComponent* FirstPressurePlate;
	UPROPERTY(EditAnywhere, Category = "Door")
	class UBoxComponent* SecondPressurePlate;
	UPROPERTY(EditAnywhere, Category = "Door")
	class UBoxComponent* Door;
	UPROPERTY(EditAnywhere, Category = "Door")
	FVector DoorOpenPos;
	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorMoveSpeed;
	UPROPERTY()
	UTimelineComponent* DoorTimeline;
	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorCurve;
	UPROPERTY(Replicated)
	int nPlayerOnPlates;

private:
	UFUNCTION()
	void OnPressurePlateBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnPressurePlateEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void HandleDoorProgress(float Value);
	UFUNCTION(NetMulticast, Reliable)
	void OpenDoor();
	UFUNCTION(Server, Reliable)
	void ServerSetPlayerOnPlates(int NewValue);
};