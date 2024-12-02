#include "CoinMan_GameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"
#include <Kismet/GameplayStatics.h>



ACoinMan_GameMode::ACoinMan_GameMode() {

	PrimaryActorTick.bCanEverTick = true;
}


void ACoinMan_GameMode::BeginPlay() {

	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ACoinMan_GameMode::SpawnCollectables,
		FMath::RandRange(1, 3), true);

}

void ACoinMan_GameMode::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

}

void ACoinMan_GameMode::SpawnCollectables()
{
	int gen_charger = 0;
	while (GetNumberOfItems(ChargerItem) < Max_Chargers_Num && gen_charger < Spawn_Charger_Freq) {
		if (Spawn(ChargerItem)) gen_charger++;

	}
	int gen_coins = 0;
	while (GetNumberOfItems(CoinItem) < Max_Coins_Num && gen_coins < Spawn_Coin_Freq) {
		if (Spawn(CoinItem)) gen_coins++;

	}
	

}

bool ACoinMan_GameMode::Spawn(TSubclassOf<AActor> Item) {

	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector StartLocation(RandX, RandY, Spawn_Z_Max);

	FVector SpawnLocation;
	if (TraceForSpawnLocation(StartLocation, SpawnLocation))
	{
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

		SpawnLocation.Z += 20;

		GetWorld()->SpawnActor(Item, &SpawnLocation, &SpawnRotation);

		return true;
	}
	return false;
}

bool ACoinMan_GameMode::TraceForSpawnLocation(FVector Start, FVector& OutLocation)
{
	FVector End(Start.X, Start.Y, Spawn_Z_Min);
	FHitResult HitResult;

	FCollisionQueryParams QueryParams;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
	{
		if (HitResult.GetActor() && HitResult.GetActor()->Tags.Contains(FName("spawn")))
		{
			OutLocation = HitResult.Location;
			return true;
		}
	}

	return false;
}

int32 ACoinMan_GameMode::GetNumberOfItems(TSubclassOf<AActor> ActorClass)
{
	if (!ActorClass) return 0;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass, FoundActors);

	return FoundActors.Num();
}
