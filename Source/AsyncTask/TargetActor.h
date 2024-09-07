// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoolChanged, bool, NewBoolValue);
class UStaticMeshComponent;

UCLASS()
class ASYNCTASK_API ATargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetActor();

	void ChangeBoolValue(const bool& newVal);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool m_bHit;
	bool m_bOverlapped;


	UPROPERTY(Replicated, ReplicatedUsing=OnRep_BoolValueChanged)
	bool m_TargetActorBool;
	

	UFUNCTION()
	void OnRep_BoolValueChanged();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void MulticastChangeBool(bool newVal);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerChangeBool(bool newVal);

	/*UFUNCTION(ServiceRequest)
	void RequestChangeBool(bool newVal);

	UFUNCTION(ServiceResponse)
	void ResponseChangeBool();*/

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	FOnBoolChanged OnBoolChanged;

	UFUNCTION()
	void OnStaticMeshCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	bool GetBoolValue() const { return m_TargetActorBool; }
};
