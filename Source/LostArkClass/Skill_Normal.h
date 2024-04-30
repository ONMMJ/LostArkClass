// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSkill.h"
#include "Skill_Normal.generated.h"

UCLASS()
class LOSTARKCLASS_API ASkill_Normal : public ABaseSkill
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_Normal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ABaseSkill을(를) 통해 상속됨
	virtual void UseSkill_Implementation() override;
	virtual void OnSkill_Implementation() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
