#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CoinMan_GameMode.generated.h"

UCLASS()
class COLLECTCOINS3DPERSON_API ACoinMan_GameMode : public AGameMode
{

	GENERATED_BODY()

	ACoinMan_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> CoinItem;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ChargerItem;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Max;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Max;

	UPROPERTY(EditAnywhere)
		float Spawn_Z_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_Z_Max;

	UPROPERTY(EditAnywhere)
		int32 Spawn_Coin_Freq;

	UPROPERTY(EditAnywhere)
		int32 Spawn_Charger_Freq;

	UPROPERTY(EditAnywhere)
		int32 Max_Coins_Num;

	UPROPERTY(EditAnywhere)
		int32 Max_Chargers_Num;

	void SpawnCollectables();
	bool Spawn(TSubclassOf<AActor> Item);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Utilities")
		int32 GetNumberOfItems(TSubclassOf<AActor> ActorClass);

	bool TraceForSpawnLocation(FVector Start, FVector& OutLocation);
};
