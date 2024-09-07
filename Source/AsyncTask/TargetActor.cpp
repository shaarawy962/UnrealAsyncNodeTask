// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetActor.h"
#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"
#include "MyPawn.h"

UE_DISABLE_OPTIMIZATION

// Sets default values
ATargetActor::ATargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	RootComponent = StaticMeshComp;
	m_TargetActorBool = false;
	m_bOverlapped = false;
	m_bHit = false;
	if (StaticMeshComp)
	{
		StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ATargetActor::OnStaticMeshCompBeginOverlap);
	}

}

void ATargetActor::ChangeBoolValue(const bool& newVal)
{
	if (newVal != m_TargetActorBool)
	{
		if (OnBoolChanged.IsBound())
			OnBoolChanged.Broadcast(newVal);
	}
	if (OnBoolChanged.IsBound())
		OnBoolChanged.Broadcast(newVal);
	m_TargetActorBool = newVal;
}

// Called when the game starts or when spawned
void ATargetActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("The door is spawned on the server."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The door is not owned by the server."));
	}
	
}

void ATargetActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATargetActor, m_TargetActorBool);
}

void ATargetActor::OnRep_BoolValueChanged()
{
	if (OnBoolChanged.IsBound())
		OnBoolChanged.Broadcast(m_TargetActorBool);
}

void ATargetActor::MulticastChangeBool_Implementation(bool newVal)
{	
	if (HasAuthority())
		ChangeBoolValue(newVal);
}

bool ATargetActor::MulticastChangeBool_Validate(bool newVal)
{
	return true;
}

void ATargetActor::ServerChangeBool_Implementation(bool newVal)
{
	if (HasAuthority())
		ChangeBoolValue(newVal);
}

bool ATargetActor::ServerChangeBool_Validate(bool newVal)
{
	return true;
}

// Called every frame
void ATargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetActor::OnStaticMeshCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_bOverlapped) return;
	m_bOverlapped = true;

	if (HasAuthority())
	{
		ChangeBoolValue(!m_TargetActorBool);
	}
	else
	{
		if (AMyPawn* myPawn = Cast<AMyPawn>(OtherActor))
		{
			myPawn->ServerOverlappedWithActor(this);
		}
	}
}


void ATargetActor::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]: Called On Server"), ANSI_TO_TCHAR(__FUNCTION__));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]: Called On Client"), ANSI_TO_TCHAR(__FUNCTION__));
	}
}

UE_ENABLE_OPTIMIZATION