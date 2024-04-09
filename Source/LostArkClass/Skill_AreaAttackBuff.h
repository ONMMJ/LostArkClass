// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSkill.h"
#include "Skill_AreaAttackBuff.generated.h"

UCLASS()
class LOSTARKCLASS_API ASkill_AreaAttackBuff : public ABaseSkill
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASkill_AreaAttackBuff();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Decal, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* Decal_MaxRange;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Decal, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* Decal_AttackRange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ABaseSkill을(를) 통해 상속됨
	void UseSkill(APawn* Player) override;
};
