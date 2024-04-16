// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARKCLASS_API UBaseItem : public UObject
{
	GENERATED_BODY()


public:

	FString FileName;

	UPROPERTY()
	UTexture2D* ItemIcon;

	UPROPERTY()
	int Count;

	UFUNCTION(BlueprintNativeEvent)
    void UseItem();	

	UFUNCTION()
	void SetIconTexture();
};
