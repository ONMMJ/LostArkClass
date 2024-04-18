// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Identity.h"

ASkill_Identity::ASkill_Identity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_Identity::BeginPlay()
{
	Super::BeginPlay();

	TArray<FIdentityItemInfo> infoList = static_cast<TArray<FIdentityItemInfo>>(ItemList_Init);
	for (FIdentityItemInfo ItemInfo : infoList)
	{
		ItemList.Add(&ItemInfo);
	}

	for (FIdentityItemInfo* ItemInfo : ItemList)
	{
		ItemInfo->Init();
	}

	if (ItemList.Num() > 0)
	{
		NowItem = ItemList[ItemNum];
	}

	Test_Item = NewObject<UBaseItem>(Test_Init);
	UE_LOG(LogTemp, Error, TEXT("@@@@@@%s"), *Test_Item->test)
}

void ASkill_Identity::UseSkill_Implementation()
{
	Super::UseSkill_Implementation();
}

void ASkill_Identity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkill_Identity::AddIdentity(int amount)
{
	Identity += amount;
	if (Identity > MaxIdentity)
		Identity = MaxIdentity;
}

bool ASkill_Identity::UseIdentity(int bubbleCount)
{
	int UseAmount = bubbleCount * 100;
	if (Identity >= UseAmount)
	{
		Identity -= UseAmount;
		return true;
	}
	return false;
}

void ASkill_Identity::Click_Z_Button()
{
	ItemNum++;
	int MaxNum = ItemList.Num();
	if (ItemNum < MaxNum)
	{
		NowItem = ItemList[ItemNum];
	}
	else if (ItemNum == MaxNum)
	{
		IsBuff = true;
	}
	else
	{
		IsBuff = false;
		ItemNum = 0;
		NowItem = ItemList[ItemNum];
	}
}

void ASkill_Identity::Click_X_Button()
{
	if (IsBuff)
	{
		//버프
	}
	else
	{
		//아이템분배
	}
}

UTexture2D* ASkill_Identity::GetItemIcon()
{
	if (IsBuff)
	{
		return SkillIcon;
	}
	else
	{
		if (NowItem)
		{
			//UE_LOG(LogTemp, Error, TEXT("NowItem"));
			if (NowItem->Item)
			{
				UE_LOG(LogTemp, Error, TEXT("@@@@@@%s"), *Test_Item->test)
				//UE_LOG(LogTemp, Error, TEXT("NowItem->Item"));
				/*if (NowItem->Item->ItemIcon)
				{
					UE_LOG(LogTemp, Error, TEXT("NowItem->Item->ItemIcon"));
					return NowItem->Item->ItemIcon;
				}*/

			}
		}
	}
	return nullptr;
}
