// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSkill.h"
#include "BaseItem.h"
#include "Skill_Identity.generated.h"

USTRUCT(BlueprintType)
struct FIdentityItemInfo
{
	GENERATED_BODY()

	FIdentityItemInfo() {
		if (Item_Init)
		{
			Item = NewObject<UBaseItem>(Item_Init);
		}
	}
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
	bool IsBuff = false;
	FIdentityItemInfo* NowItem;
public:
	// Sets default values for this actor's properties
	ASkill_Identity();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	int Identity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TArray<FIdentityItemInfo> ItemList;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ABaseSkill을(를) 통해 상속됨
	virtual void UseSkill_Implementation() override;

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
	void Click_Y_Button();
};
