// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Identity.h"
#include "LostArkClassPlayerController.h"

ASkill_Identity::ASkill_Identity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuffArea = CreateDefaultSubobject<USphereComponent>(TEXT("BuffArea"));
	BuffArea->InitSphereRadius(50.0f); // 반지름 설정
	BuffArea->SetCollisionProfileName(TEXT("BuffArea")); // 충돌 프로필 설정
	BuffArea->SetupAttachment(RootComponent); // 루트에 연결되도록 설정
}

void ASkill_Identity::BeginPlay()
{
	Super::BeginPlay();

	IsActive = false;
	for (TSubclassOf<UBaseItem> Item_Init : ItemList_Init)
	{
		ItemList.Add(NewObject<UBaseItem>(this, Item_Init));
	}

	if (ItemList.Num() > 0)
	{
		NowItem = ItemList[ItemNum];
	}
	else
	{
		NowItem = nullptr;
	}
}

void ASkill_Identity::UseSkill_Implementation()
{
	Super::UseSkill_Implementation();
}


void ASkill_Identity::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOtherPlayer* OtherPlayer = Cast<AOtherPlayer>(OtherActor);
	if (OtherPlayer)
	{
		PlayerListInBuffArea.Add(OtherPlayer);
	}
}

void ASkill_Identity::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AOtherPlayer* OtherPlayer = Cast<AOtherPlayer>(OtherActor);
	if (OtherPlayer)
	{
		PlayerListInBuffArea.Remove(OtherPlayer);
	}
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
		if (UseIdentity(2))
		{
			IsActive = true;
			PlayAnimation();
		}
	}
	else
	{
		if (UseIdentity(NowItem->BubbleCount))
		{
			IsActive = true;
			PlayAnimation();
		}
	}
}

void ASkill_Identity::OnSkill_Implementation()
{
	if (IsBuff)
	{
	}
	else
	{
		if (PlayerController)
		{
			PlayerController->IdentityItem = NowItem;
		}
	}
}