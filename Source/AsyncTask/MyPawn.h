// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "MyPawn.generated.h"

UCLASS()
class ASYNCTASK_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category=Input)
	class UInputConfig* PlayerInputCFG;

	UPROPERTY(EditDefaultsOnly, Category=Input)
	class UInputMappingContext* InputMapping;

	void MovementActionHandler(const FInputActionValue& InputVal);
	void LookingActionHandler(const FInputActionValue& InputVal);

	void Move(FVector2D MoveVec);
	void Look(FVector2D LookingDir);

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

	UPROPERTY(EditDefaultsOnly)
	float LookRate;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerOverlappedWithActor(AActor* otherActor);

};
