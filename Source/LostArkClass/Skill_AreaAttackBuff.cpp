// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_AreaAttackBuff.h"
#include "Components/DecalComponent.h"
#include "LostArkClassPlayerController.h"

ASkill_AreaAttackBuff::ASkill_AreaAttackBuff()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create a root component
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    SetRootComponent(RootComponent);

    // Create and attach decal component
    Decal_MaxRange = CreateDefaultSubobject<UDecalComponent>(TEXT("MaxRange"));
    Decal_MaxRange->SetupAttachment(RootComponent);
    Decal_MaxRange->DecalSize = FVector(1000.0f, 1000.0f, 1000.0f);
    Decal_MaxRange->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f)); // Optional: rotate the decal
    Decal_MaxRange->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Optional: adjust the decal's position
    
    // 스태틱 메쉬 컴포넌트 생성 및 설정
    Plane_AttackRange = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttackRange"));
    Plane_AttackRange->SetupAttachment(RootComponent);

}

void ASkill_AreaAttackBuff::BeginPlay()
{
	Super::BeginPlay();

    // 다이나믹 머터리얼
    MaterialInstance = Plane_AttackRange->CreateDynamicMaterialInstance(0);
    InReach = true;

    SetActive_AttackRange(false);
}

void ASkill_AreaAttackBuff::UseSkill(APawn* Player)
{
    SetActive_AttackRange(true);
    Decal_MaxRange->SetWorldLocation(Player->GetActorLocation());

    PlayerController->ActiveSkill.Clear();
    PlayerController->ActiveSkill.BindDynamic(this, &ASkill_AreaAttackBuff::ActiveSkill);

    PlayerController->EndSkill.Clear();
    PlayerController->EndSkill.BindDynamic(this, &ASkill_AreaAttackBuff::EndSkill);
}

bool ASkill_AreaAttackBuff::ActiveSkill()
{
    if(InReach)
    {
        AAreaOfEffect* aoe = GetWorld()->SpawnActor<AAreaOfEffect>(SpawnActor);
        aoe->SetActorLocation(ObjectImpactPoint);
        SetActive_AttackRange(false);
        return false;
    }
    return true;
}

void ASkill_AreaAttackBuff::EndSkill()
{
    UE_LOG(LogTemp, Error, TEXT("fffffffffffffff"));
    SetActive_AttackRange(false);
}

void ASkill_AreaAttackBuff::SetActive_AttackRange(bool IsActive)
{
    Decal_MaxRange->SetHiddenInGame(!IsActive);
    Plane_AttackRange->SetHiddenInGame(!IsActive);
}

void ASkill_AreaAttackBuff::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerController)
    {
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
            ObjectImpactPoint = HitResult.ImpactPoint;
            ObjectImpactPoint.Z = ObjectImpactPoint.Z;
            // 데칼 컴포넌트 위치 업데이트
            if (Plane_AttackRange)
            {
                Plane_AttackRange->SetWorldLocation(ObjectImpactPoint);

                FVector Center = Decal_MaxRange->GetRelativeLocation();
                FVector Attack = Plane_AttackRange->GetRelativeLocation();
                Center.Z = 0;
                Attack.Z = 0;
                double distance = FVector::Distance(Center, Attack);
                FName ParameterName("InReach");
                InReach = distance <= 500.f;
                float par = InReach ? 1.0f : 0.0f;
                if (MaterialInstance)
                    MaterialInstance->SetScalarParameterValue(ParameterName, par);
            }
        }
    }
}
