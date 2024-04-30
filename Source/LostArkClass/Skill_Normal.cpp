// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Normal.h"

// Sets default values
ASkill_Normal::ASkill_Normal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkill_Normal::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkill_Normal::UseSkill_Implementation()
{
	Super::UseSkill_Implementation();
}

void ASkill_Normal::OnSkill_Implementation()
{
	Super::OnSkill_Implementation();
}

// Called every frame
void ASkill_Normal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

