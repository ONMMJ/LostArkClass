// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSkill.generated.h"

UENUM(BlueprintType)
enum class ESkillType
{
	Normal,
	Charge,
	Casting,
	Point,
	None,
};

UCLASS()
class LOSTARKCLASS_API ABaseSkill : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerController")
	class ALostArkClassPlayerController* PlayerController;

public:	
	// Sets default values for this actor's properties
	ABaseSkill();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInfo")
	class UTexture2D* SkillIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInfo")
	ESkillType SkillType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInfo")
	int IdentityAmount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInfo")
	bool IsStack = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillInfo")
	bool IsReady;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillInfo")
	int StackCount;
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

	UFUNCTION(BlueprintNativeEvent)
	void UseSkill();

	UFUNCTION()
	virtual bool ActiveSkill();
	UFUNCTION(BlueprintCallable)
	virtual void EndSkill();

	UFUNCTION(BlueprintCallable)
	virtual void LookTarget();

	UFUNCTION(BlueprintCallable)
	void HitEnemy();

	UFUNCTION(BlueprintCallable)
	void ResetCooldown();
};
