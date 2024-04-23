// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkill.h"
#include "Engine/Texture2D.h"
#include "LostArkClassPlayerController.h"

// Sets default values
ABaseSkill::ABaseSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSkill::BeginPlay()
{
	Super::BeginPlay();
	IsReady = true;
    StackCount = 2;
	// PlayerController 가져오기
	PlayerController = Cast<ALostArkClassPlayerController>(GetWorld()->GetFirstPlayerController());
}

void ABaseSkill::UseSkill_Implementation()
{
	PlayerController->ActiveSkill.Clear();
	PlayerController->ActiveSkill.BindDynamic(this, &ABaseSkill::ActiveSkill);
}

bool ABaseSkill::ActiveSkill()
{
	return false;
}

void ABaseSkill::EndSkill()
{
	PlayerController->EndSkill(this);
}

void ABaseSkill::LookTarget()
{
    // 플레이어 마우스 방향으로 회전
    // 마우스 위치 가져오기
    FVector2D MousePosition;
    PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

    // 레이캐스트를 통해 마우스가 충돌한 위치 확인하기
    FHitResult HitResult;
    PlayerController->GetHitResultAtScreenPosition(MousePosition, ECollisionChannel::ECC_Visibility, false, HitResult);

    // 레이캐스트가 성공한 경우
    if (HitResult.bBlockingHit)
    {
        // 오브젝트의 충돌한 위치 얻기
        FVector ObjectImpactPoint = HitResult.ImpactPoint;
        ObjectImpactPoint.Z = 0;

        APawn* player = PlayerController->GetPawn();
        FVector playerPos = player->GetActorLocation();
        playerPos.Z = 0;

        FVector Direction = ObjectImpactPoint - playerPos;
        Direction.Normalize();

        FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
        player->SetActorRotation(Rotation);
    }
    if (IsStack)
    {
        if(StackCount == 2)
            NowCoolDown = MaxCoolDown;
        StackCount--;
        if (StackCount > 0)
            IsReady = true;
        else
            IsReady = false;
    }
    else
    {
        IsReady = false;
        NowCoolDown = MaxCoolDown;
    }
}

void ABaseSkill::ResetCooldown()
{
    if (IsStack)
    {
        if (StackCount < 2)
        {
            StackCount++;
        }
    }
    IsReady = true;
}

// Called every frame
void ABaseSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (IsStack)
    {
        if (StackCount<2)
        {
            NowCoolDown -= DeltaTime;
            if (NowCoolDown <= 0)
            {
                StackCount++;
                NowCoolDown = MaxCoolDown;
            }
            if (StackCount > 0)
                IsReady = true;
        }
    }
    else
    {
        if (!IsReady)
        {
            NowCoolDown -= DeltaTime;
            if (NowCoolDown <= 0)
                IsReady = true;
        }
    }
}
void ABaseSkill::HitEnemy()
{
    PlayerController->IdentitySkill->AddIdentity(IdentityAmount);
}