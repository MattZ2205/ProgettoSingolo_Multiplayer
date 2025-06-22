#include "Door_PressurePlates.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

ADoor_PressurePlates::ADoor_PressurePlates()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	Door = CreateDefaultSubobject<UBoxComponent>(TEXT("Door"));
	FirstPressurePlate = CreateDefaultSubobject<UBoxComponent>(TEXT("FirstPressurePlate"));
	SecondPressurePlate = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondPressurePlate"));
	SetRootComponent(SecondPressurePlate);
	SetRootComponent(FirstPressurePlate);
	SetRootComponent(Door);
	nPlayerOnPlates = 0;

	FirstPressurePlate->OnComponentBeginOverlap.AddDynamic(this, &ADoor_PressurePlates::OnPressurePlateBeginOverlap);
	SecondPressurePlate->OnComponentBeginOverlap.AddDynamic(this, &ADoor_PressurePlates::OnPressurePlateBeginOverlap);
	FirstPressurePlate->OnComponentEndOverlap.AddDynamic(this, &ADoor_PressurePlates::OnPressurePlateEndOverlap);
	SecondPressurePlate->OnComponentEndOverlap.AddDynamic(this, &ADoor_PressurePlates::OnPressurePlateEndOverlap);

	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
}

void ADoor_PressurePlates::BeginPlay()
{
	Super::BeginPlay();
	if (DoorCurve && DoorTimeline)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleDoorProgress"));
		DoorTimeline->AddInterpFloat(DoorCurve, ProgressFunction);
	}
}

void ADoor_PressurePlates::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DoorTimeline)
		DoorTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
}

void ADoor_PressurePlates::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADoor_PressurePlates, nPlayerOnPlates);
}

void ADoor_PressurePlates::ServerSetPlayerOnPlates_Implementation(int NewValue)
{
	nPlayerOnPlates = NewValue;
	if (nPlayerOnPlates >= 2) OpenDoor();
}

void ADoor_PressurePlates::OnPressurePlateBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		ServerSetPlayerOnPlates(nPlayerOnPlates + 1);
	}
	else
	{
		nPlayerOnPlates++;
		if (nPlayerOnPlates >= 2) OpenDoor();
	}
}

void ADoor_PressurePlates::OnPressurePlateEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!HasAuthority()) ServerSetPlayerOnPlates(nPlayerOnPlates - 1);
	else nPlayerOnPlates--;
}

void ADoor_PressurePlates::OpenDoor_Implementation()
{
	if (DoorTimeline) DoorTimeline->PlayFromStart();
}

void ADoor_PressurePlates::HandleDoorProgress(float Value)
{
	SetActorLocation(FMath::Lerp(GetActorLocation(), DoorOpenPos, DoorMoveSpeed * GetWorld()->GetDeltaSeconds()));
}