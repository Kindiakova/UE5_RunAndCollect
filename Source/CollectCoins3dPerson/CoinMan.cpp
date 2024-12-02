#include "CoinMan.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"


ACoinMan::ACoinMan()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll= false;

	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	beDead = false;
	Power = 100.0f;
	Score = 0;

}

void ACoinMan::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACoinMan::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ACoinMan::OnHit);
	if (Player_Main_Widget_Class != nullptr) {

		Player_Main_Widget = CreateWidget(GetWorld(), Player_Main_Widget_Class);
		Player_Main_Widget->AddToViewport();
	}


	
}

void ACoinMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Power -= DeltaTime * Power_Treshold;
	if (Power <= 0 || GetActorLocation().Z < Death_Level) {

		if (!beDead) {

			beDead = true;
			GetMesh()->SetSimulatePhysics(true);

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(
				UnusedHandle, this, &ACoinMan::RestartGame, 3.0f, false);

		}

	}

}

void ACoinMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUP", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACoinMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACoinMan::MoveRight);
	
}

void ACoinMan::MoveForward(float Axis)
{
	if (!beDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);

	}
}

void ACoinMan::MoveRight(float Axis)
{
	if (!beDead) {

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);

	}
}

void ACoinMan::RestartGame()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (PC->PlayerCameraManager)
		{
			PC->PlayerCameraManager->StartCameraFade(0.f, 1.f, 2.f, FLinearColor::Black, true, true);
		}
	}
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			if (Player_Death_Widget_Class != nullptr) {

				Player_Death_Widget = CreateWidget(GetWorld(), Player_Death_Widget_Class);
				Player_Death_Widget->AddToViewport();

				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				if (PlayerController)
				{
					PlayerController->bShowMouseCursor = true;

					FInputModeUIOnly InputMode;
					PlayerController->SetInputMode(InputMode);
				}
			}
			else
				UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

		}, 3, false);

}

void ACoinMan::OnBeginOverlap(UPrimitiveComponent* HitComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) 
{

	if (OtherActor->ActorHasTag("Charger")) {
		Power = FMath::Min(Power + 10.0f, 100.0f);

		OtherActor->Destroy();
	}

	if (OtherActor->ActorHasTag("Coin")) {
		++Score;

		OtherActor->Destroy();
	}

	if (OtherActor->ActorHasTag("death")) {

		if (!beDead) {

			beDead = true;

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(
				UnusedHandle, this, &ACoinMan::RestartGame, 1.0f, false);


		}
	}
}

void ACoinMan::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("death")) {

		if (!beDead) {

			beDead = true;

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(
				UnusedHandle, this, &ACoinMan::RestartGame, 1.0f, false);


		}
	}
}