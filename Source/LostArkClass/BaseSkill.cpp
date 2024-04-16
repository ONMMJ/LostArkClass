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
	// PlayerController ��������
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
    // �÷��̾� ���콺 �������� ȸ��
    // ���콺 ��ġ ��������
    FVector2D MousePosition;
    PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

    // ����ĳ��Ʈ�� ���� ���콺�� �浹�� ��ġ Ȯ���ϱ�
    FHitResult HitResult;
    PlayerController->GetHitResultAtScreenPosition(MousePosition, ECollisionChannel::ECC_Visibility, false, HitResult);

    // ����ĳ��Ʈ�� ������ ���
    if (HitResult.bBlockingHit)
    {
        // ������Ʈ�� �浹�� ��ġ ���
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
    NowCoolDown = MaxCoolDown;
    IsReady = false;
}

// Called every frame
void ABaseSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsReady)
	{
		NowCoolDown -= DeltaTime;
		if (NowCoolDown <= 0)
			IsReady = true;
	}
}
