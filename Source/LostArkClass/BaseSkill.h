// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSkill.generated.h"

UCLASS()
class LOSTARKCLASS_API ABaseSkill : public AActor
{
	GENERATED_BODY()

protected:
	class ALostArkClassPlayerController* PlayerController;

public:	
	// Sets default values for this actor's properties
	ABaseSkill();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillInfo")
	bool IsReady;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillInfo")
	float NowCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInfo")
	float MaxCoolDown;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void UseSkill(APawn* Player);
};
