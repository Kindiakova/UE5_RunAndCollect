#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Blueprint/UserWidget.h"


#include "CoinMan.generated.h"

UCLASS()
class COLLECTCOINS3DPERSON_API ACoinMan : public ACharacter
{
	GENERATED_BODY()

public:
	ACoinMan();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	bool beDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Power;
	UPROPERTY(EditAnywhere)
		float Power_Treshold;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int Score;

	UPROPERTY(EditAnywhere)
		float Death_Level;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* HitComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Player_Main_Widget_Class;
	UUserWidget* Player_Main_Widget;


	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Player_Death_Widget_Class;
	UUserWidget* Player_Death_Widget;

	void RestartGame();


protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
