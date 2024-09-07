// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WaitForBoolChange.generated.h"

class ATargetActor;
class AListeningActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAsyncBoolChange, bool, NewBoolValue);

/**
 * 
 */
UCLASS()
class ASYNCTASK_API UWaitForBoolChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintAssignable)
    FOnAsyncBoolChange OnChange;

	virtual void Activate() override;

	virtual void SetReadyToDestroy() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))	
	static UWaitForBoolChange* WaitForBoolChange(AActor* ListenActor, AActor* TargetActor);

	
	

private:
	
	UPROPERTY()
	ATargetActor* TargetActor;

	UPROPERTY()
	AListeningActor* ListenActor;

	UFUNCTION()
	void OnBoolChanged(bool NewBoolValue);

	

};
