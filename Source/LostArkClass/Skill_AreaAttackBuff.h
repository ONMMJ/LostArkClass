// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSkill.h"
#include "AreaOfEffect.h"
#include "Skill_AreaAttackBuff.generated.h"

UCLASS()
class LOSTARKCLASS_API ASkill_AreaAttackBuff : public ABaseSkill
{
	GENERATED_BODY()

	class USceneComponent* RootComponent;
	class UMaterialInstanceDynamic* MaterialInstance;
	FVector ObjectImpactPoint;
	bool InReach;
	bool IsPlaying;
public:
	// Sets default values for this actor's properties
	ASkill_AreaAttackBuff();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Range")
	class UDecalComponent* Decal_MaxRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Range")
	class UStaticMeshComponent* Plane_AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	TSubclassOf<AAreaOfEffect> SpawnActor;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ABaseSkill을(를) 통해 상속됨
	virtual void UseSkill_Implementation() override;

	bool ActiveSkill() override;
	UFUNCTION()
	void CancelSkill();

	UFUNCTION()
	void SetActive_AttackRange(bool IsActive);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
