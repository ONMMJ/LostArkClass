// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AreaOfEffect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitEnemy);

UCLASS()
class LOSTARKCLASS_API AAreaOfEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAreaOfEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FHitEnemy HitEnemyDelegate;

	UFUNCTION(BlueprintCallable)
	void TriggerHitEnemy();
};
