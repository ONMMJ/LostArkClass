// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSkill.h"
#include "BaseItem.h"
#include "OtherPlayer.h"
#include "Components/SphereComponent.h"
#include "Skill_Identity.generated.h"

USTRUCT(BlueprintType)
struct FIdentityItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseItem> Item_Init;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BubbleCount;
	UPROPERTY()
	UBaseItem* Item;
};

UCLASS()
class LOSTARKCLASS_API ASkill_Identity : public ABaseSkill
{
	GENERATED_BODY()

	const int MaxIdentity = 300;

	int ItemNum = 0;

	bool IsActive;
public:
	// Sets default values for this actor's properties
	ASkill_Identity();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	USphereComponent* BuffArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	UTexture2D* Test;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	int Identity = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))

	bool IsBuff = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AOtherPlayer*> PlayerListInBuffArea;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UBaseItem>> ItemList_Init;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UBaseItem*> ItemList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseItem* NowItem;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ABaseSkill을(를) 통해 상속됨
	virtual void UseSkill_Implementation() override;
	virtual void OnSkill_Implementation() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddIdentity(int amount);
	UFUNCTION(BlueprintCallable)
	bool UseIdentity(int bubbleCount);
	UFUNCTION(BlueprintCallable)
	void Click_Z_Button();
	UFUNCTION(BlueprintCallable)
	void Click_X_Button();
};
