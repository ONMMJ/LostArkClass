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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseItem> Item_Init;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BubbleCount;

	UPROPERTY()
	UBaseItem* Item;

	void Init()
	{
		if (Item_Init)
		{
			UE_LOG(LogTemp, Error, TEXT("@@@@@@@@@@@@@@@@@@@"));
			Item = NewObject<UBaseItem>(Item_Init);
			if (Item)
			{
				UE_LOG(LogTemp, Error, TEXT("True"));
			}
			else 
			{
				UE_LOG(LogTemp, Error, TEXT("False"));
			}
		}
	}
};

UCLASS()
class LOSTARKCLASS_API ASkill_Identity : public ABaseSkill
{
	GENERATED_BODY()

	const int MaxIdentity = 300;

	int ItemNum = 0;
	FIdentityItemInfo* NowItem;
	TArray<FIdentityItemInfo*> ItemList;
public:
	// Sets default values for this actor's properties
	ASkill_Identity();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	UTexture2D* Test;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	int Identity = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))

	bool IsBuff = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TArray<FIdentityItemInfo> ItemList_Init;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseItem> Test_Init;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBaseItem* Test_Item;

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
	void Click_X_Button();

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetItemIcon();
};
