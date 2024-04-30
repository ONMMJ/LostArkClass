// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class LOSTARKCLASS_API UBaseItem : public UObject
{
	GENERATED_BODY()


public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	UTexture2D* ItemIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	int BubbleCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Info")
	float Cooldown = 5;

	UPROPERTY()
	int Count;

	UFUNCTION(BlueprintNativeEvent)
    void UseItem();	
};
