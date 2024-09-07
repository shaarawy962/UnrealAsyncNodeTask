// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitForBoolChange.h"
#include "ListeningActor.h"
#include "TargetActor.h"

void UWaitForBoolChange::Activate()
{
	Super::Activate();

	ATargetActor* m_TargetActor = Cast<ATargetActor>(TargetActor);
	AListeningActor* m_ListenActor = Cast<AListeningActor>(ListenActor);
	
	if (TargetActor && ListenActor)
	{
		TargetActor->OnBoolChanged.AddDynamic(this, &UWaitForBoolChange::OnBoolChanged);
	}
}

void UWaitForBoolChange::SetReadyToDestroy()
{

}

//bool UWaitForBoolChange::WaitForBoolChange(AActor* ListenActor, AActor* TargetActor)
//{
//	
//}

UWaitForBoolChange* UWaitForBoolChange::WaitForBoolChange(AActor* ListenActor, AActor* TargetActor)
{
	UWaitForBoolChange* WaitForBoolChangeNode = NewObject<UWaitForBoolChange>();


	ATargetActor* m_TargetActor = Cast<ATargetActor>(TargetActor);
	AListeningActor* m_ListenActor = Cast<AListeningActor>(ListenActor);

	if (m_TargetActor && m_ListenActor)
	{
		WaitForBoolChangeNode->TargetActor = m_TargetActor;
		WaitForBoolChangeNode->ListenActor = m_ListenActor;
	}

	return WaitForBoolChangeNode;
}

void UWaitForBoolChange::OnBoolChanged(bool NewBoolValue)
{
	OnChange.Broadcast(NewBoolValue);
}
