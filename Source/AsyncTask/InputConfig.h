// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfig.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ASYNCTASK_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category=Input)
	UInputAction* IA_Move;


	UPROPERTY(EditDefaultsOnly, Category=Input)
	UInputAction* IA_Look;
	
};
