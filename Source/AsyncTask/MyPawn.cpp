// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputConfig.h"
#include "TargetActor.h"
UE_DISABLE_OPTIMIZATION
// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementSpeed = 10.f;
	bReplicates = true;
	LookRate = 50.0f;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PC = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputSubsystem)
	{
		EnhancedInputSubsystem->ClearAllMappings();
		EnhancedInputSubsystem->AddMappingContext(InputMapping, 0);
		if (EnhancedInputComp && PlayerInputCFG)
		{
			EnhancedInputComp->BindAction(PlayerInputCFG->IA_Move, ETriggerEvent::Triggered, this, &AMyPawn::MovementActionHandler);
			EnhancedInputComp->BindAction(PlayerInputCFG->IA_Look, ETriggerEvent::Triggered, this, &AMyPawn::LookingActionHandler);
		}
	}
	

}

void AMyPawn::MovementActionHandler(const FInputActionValue& InputVal)
{
	FVector2D MovementDir = InputVal.Get<FVector2D>();
	Move(MovementDir);
}

void AMyPawn::LookingActionHandler(const FInputActionValue& InputVal)
{
	FVector2D lookingDir = InputVal.Get<FVector2D>();
	Look(lookingDir);
}

void AMyPawn::Move(FVector2D MoveVec)
{
	bool bIsForward = MoveVec.X > 0;
	bool bIsBackward= MoveVec.X < 0;
	bool bIsRight = MoveVec.Y > 0;
	bool bIsLeft = MoveVec.Y < 0;

	if (bIsForward){
		FVector Location = GetActorLocation();
		FVector LookDir = GetController()->GetControlRotation().Vector();
		FVector NewLocation = Location + (LookDir * 10);
		SetActorLocation(NewLocation);
	}

	if (bIsBackward)
	{
		FVector Location = GetActorLocation();
		FVector LookDir = GetController()->GetControlRotation().Vector() * -1;
		FVector NewLocation = Location + (LookDir * 10);
		SetActorLocation(NewLocation);
	}
}


void AMyPawn::Look(FVector2D LookingDir)
{
	/*FRotator Rotation = GetActorRotation();

	FRotator NewRotation = */

	float XVal = LookingDir.X;
	float YVal = LookingDir.Y;

	AddControllerPitchInput(YVal);
	AddControllerYawInput(XVal);
}

UE_ENABLE_OPTIMIZATION

void AMyPawn::ServerOverlappedWithActor_Implementation(AActor* otherActor)
{
	if (otherActor && otherActor->HasAuthority())
	{
		ATargetActor* TargetActor = Cast<ATargetActor>(otherActor);
		if (TargetActor) TargetActor->ChangeBoolValue(!TargetActor->GetBoolValue());
	}
}

bool AMyPawn::ServerOverlappedWithActor_Validate(AActor* otherActor)
{
	return true;
}
