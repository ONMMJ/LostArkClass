// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaOfEffect.h"

// Sets default values
AAreaOfEffect::AAreaOfEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAreaOfEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAreaOfEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAreaOfEffect::TriggerHitEnemy()
{
	HitEnemyDelegate.Broadcast();
}

