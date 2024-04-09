// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_AreaAttackBuff.h"
#include "Components/DecalComponent.h"

ASkill_AreaAttackBuff::ASkill_AreaAttackBuff()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create and attach decal component
    Decal_MaxRange = CreateDefaultSubobject<UDecalComponent>(TEXT("MaxRange"));
    RootComponent = Decal_MaxRange;
    Decal_MaxRange->DecalSize = FVector(100.0f, 100.0f, 100.0f);
    Decal_MaxRange->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); // Optional: rotate the decal
    Decal_MaxRange->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Optional: adjust the decal's position

    Decal_AttackRange = CreateDefaultSubobject<UDecalComponent>(TEXT("AttackRange"));
    Decal_AttackRange->SetupAttachment(RootComponent);
    Decal_AttackRange->DecalSize = FVector(100.0f, 100.0f, 100.0f);
    Decal_AttackRange->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); // Optional: rotate the decal
    Decal_AttackRange->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Optional: adjust the decal's position

}

void ASkill_AreaAttackBuff::BeginPlay()
{
	Super::BeginPlay();
}

void ASkill_AreaAttackBuff::UseSkill(APawn* Player)
{

}
