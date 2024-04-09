// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkill.h"
#include "LostArkClassPlayerController.h"

// Sets default values
ABaseSkill::ABaseSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSkill::BeginPlay()
{
	Super::BeginPlay();
	IsReady = true;
	// PlayerController 가져오기
	PlayerController = Cast<ALostArkClassPlayerController>(GetWorld()->GetFirstPlayerController());
}

void ABaseSkill::UseSkill(APawn* Player)
{
}

// Called every frame
void ABaseSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsReady)
	{
		NowCoolDown -= DeltaTime;
		if (NowCoolDown <= 0)
			IsReady = true;
	}
}

