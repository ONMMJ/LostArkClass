// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostArkClassPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "LostArkClassCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ALostArkClassPlayerController::ALostArkClassPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	IsActiveSkill = false;
	IsPointingSkill = false;
}

void ALostArkClassPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	IsActiveSkill = false;
	IsPointingSkill = false;

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	int count = static_cast<int>(ESkillIndex::Count);
	for (int i = 0; i < count; i++)
	{
		ABaseSkill* NewSkill = GetWorld()->SpawnActor<ABaseSkill>(*AllSkills[i]);
		if (NewSkill)
		{
			ESkillIndex key = static_cast<ESkillIndex>(i);
			SelectedSkills.Add(key, NewSkill);
		}
	}
}

void ALostArkClassPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ALostArkClassPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ALostArkClassPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ALostArkClassPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ALostArkClassPlayerController::OnTouchReleased);

		// Skill
		EnhancedInputComponent->BindAction(SetActionSkill_Q, ETriggerEvent::Started, this, &ALostArkClassPlayerController::UseSkill_Q);
		EnhancedInputComponent->BindAction(SetActionSkill_W, ETriggerEvent::Started, this, &ALostArkClassPlayerController::UseSkill_W);
		EnhancedInputComponent->BindAction(SetActionSkill_E, ETriggerEvent::Started, this, &ALostArkClassPlayerController::UseSkill_E);
		EnhancedInputComponent->BindAction(SetActionSkill_R, ETriggerEvent::Started, this, &ALostArkClassPlayerController::UseSkill_R);
		EnhancedInputComponent->BindAction(SetActionSkill_A, ETriggerEvent::Started, this, &ALostArkClassPlayerController::UseSkill_A);
		EnhancedInputComponent->BindAction(SetActionSkill_S, ETriggerEvent::Started, this, &ALostArkClassPlayerController::UseSkill_S);
		EnhancedInputComponent->BindAction(SetActionSkill_D, ETriggerEvent::Started, this, &ALostArkClassPlayerController::UseSkill_D);
		EnhancedInputComponent->BindAction(SetActionSkill_F, ETriggerEvent::Started, this, &ALostArkClassPlayerController::UseSkill_F);

		EnhancedInputComponent->BindAction(SetActionSkill_Q, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::TriggeredSkill_Q);
		EnhancedInputComponent->BindAction(SetActionSkill_W, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::TriggeredSkill_W);
		EnhancedInputComponent->BindAction(SetActionSkill_E, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::TriggeredSkill_E);
		EnhancedInputComponent->BindAction(SetActionSkill_R, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::TriggeredSkill_R);
		EnhancedInputComponent->BindAction(SetActionSkill_A, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::TriggeredSkill_A);
		EnhancedInputComponent->BindAction(SetActionSkill_S, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::TriggeredSkill_S);
		EnhancedInputComponent->BindAction(SetActionSkill_D, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::TriggeredSkill_D);
		EnhancedInputComponent->BindAction(SetActionSkill_F, ETriggerEvent::Triggered, this, &ALostArkClassPlayerController::TriggeredSkill_F);

		EnhancedInputComponent->BindAction(SetActionSkill_Q, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::CompletedSkill_Q);
		EnhancedInputComponent->BindAction(SetActionSkill_W, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::CompletedSkill_W);
		EnhancedInputComponent->BindAction(SetActionSkill_E, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::CompletedSkill_E);
		EnhancedInputComponent->BindAction(SetActionSkill_R, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::CompletedSkill_R);
		EnhancedInputComponent->BindAction(SetActionSkill_A, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::CompletedSkill_A);
		EnhancedInputComponent->BindAction(SetActionSkill_S, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::CompletedSkill_S);
		EnhancedInputComponent->BindAction(SetActionSkill_D, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::CompletedSkill_D);
		EnhancedInputComponent->BindAction(SetActionSkill_F, ETriggerEvent::Completed, this, &ALostArkClassPlayerController::CompletedSkill_F);

		// Attack
		EnhancedInputComponent->BindAction(SetActionAttack, ETriggerEvent::Started, this, &ALostArkClassPlayerController::ActiveAttack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALostArkClassPlayerController::OnInputStarted()
{
	StopMovement();
	if (IsPointingSkill)
	{
		CancelSkill.Execute();
		IsPointingSkill = false;
	}
}

// Triggered every frame when the input is held down
void ALostArkClassPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ALostArkClassPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ALostArkClassPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ALostArkClassPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ALostArkClassPlayerController::UseSkill_Q()
{
	if (SelectedSkills.Contains(ESkillIndex::Q)) 
	{
		ABaseSkill* skill = SelectedSkills[ESkillIndex::Q];
		currentSkillKey = ESkillIndex::Q;
		UseSkill(skill);
	}
}
void ALostArkClassPlayerController::UseSkill_W()
{
	if (SelectedSkills.Contains(ESkillIndex::W))
	{
		ABaseSkill* skill = SelectedSkills[ESkillIndex::W];
		currentSkillKey = ESkillIndex::W;
		UseSkill(skill);
	}
}
void ALostArkClassPlayerController::UseSkill_E()
{
	if (SelectedSkills.Contains(ESkillIndex::E))
	{
		ABaseSkill* skill = SelectedSkills[ESkillIndex::E];
		currentSkillKey = ESkillIndex::E;
		UseSkill(skill);
	}
}
void ALostArkClassPlayerController::UseSkill_R()
{
	if (SelectedSkills.Contains(ESkillIndex::R))
	{
		ABaseSkill* skill = SelectedSkills[ESkillIndex::R];
		currentSkillKey = ESkillIndex::R;
		UseSkill(skill);
	}
}
void ALostArkClassPlayerController::UseSkill_A()
{
	if (SelectedSkills.Contains(ESkillIndex::A))
	{
		ABaseSkill* skill = SelectedSkills[ESkillIndex::A];
		currentSkillKey = ESkillIndex::A;
		UseSkill(skill);
	}
}
void ALostArkClassPlayerController::UseSkill_S()
{
	if (SelectedSkills.Contains(ESkillIndex::S))
	{
		ABaseSkill* skill = SelectedSkills[ESkillIndex::S];
		currentSkillKey = ESkillIndex::S;
		UseSkill(skill);
	}
}
void ALostArkClassPlayerController::UseSkill_D()
{
	if (SelectedSkills.Contains(ESkillIndex::D))
	{
		ABaseSkill* skill = SelectedSkills[ESkillIndex::D];
		currentSkillKey = ESkillIndex::D;
		UseSkill(skill);
	}
}
void ALostArkClassPlayerController::UseSkill_F()
{
	if (SelectedSkills.Contains(ESkillIndex::F))
	{
		ABaseSkill* skill = SelectedSkills[ESkillIndex::F];
		currentSkillKey = ESkillIndex::F;
		UseSkill(skill);
	}
}

void ALostArkClassPlayerController::TriggeredSkill_Q()
{

}
void ALostArkClassPlayerController::TriggeredSkill_W()
{

}
void ALostArkClassPlayerController::TriggeredSkill_E()
{

}
void ALostArkClassPlayerController::TriggeredSkill_R()
{

}
void ALostArkClassPlayerController::TriggeredSkill_A()
{

}
void ALostArkClassPlayerController::TriggeredSkill_S()
{

}
void ALostArkClassPlayerController::TriggeredSkill_D()
{

}
void ALostArkClassPlayerController::TriggeredSkill_F()
{

}

void ALostArkClassPlayerController::CompletedSkill_Q()
{
	if (IsActiveSkill)
	{
		if (currentSkillKey != ESkillIndex::Q)
			return;

		if (currentSkillType == ESkillType::Charge || currentSkillType == ESkillType::Casting)
			ReleaseSkill.Execute();
	}
}
void ALostArkClassPlayerController::CompletedSkill_W()
{
	if (IsActiveSkill)
	{
		if (currentSkillKey != ESkillIndex::W)
			return;

		if (currentSkillType == ESkillType::Charge || currentSkillType == ESkillType::Casting)
			ReleaseSkill.Execute();
	}
}
void ALostArkClassPlayerController::CompletedSkill_E()
{
	if (IsActiveSkill)
	{
		if (currentSkillKey != ESkillIndex::E)
			return;

		if (currentSkillType == ESkillType::Charge || currentSkillType == ESkillType::Casting)
			ReleaseSkill.Execute();
	}
}
void ALostArkClassPlayerController::CompletedSkill_R()
{
	if (IsActiveSkill)
	{
		if (currentSkillKey != ESkillIndex::R)
			return;

		if (currentSkillType == ESkillType::Charge || currentSkillType == ESkillType::Casting)
			ReleaseSkill.Execute();
	}
}
void ALostArkClassPlayerController::CompletedSkill_A()
{
	if (IsActiveSkill)
	{
		if (currentSkillKey != ESkillIndex::A)
			return;

		if (currentSkillType == ESkillType::Charge || currentSkillType == ESkillType::Casting)
			ReleaseSkill.Execute();
	}
}
void ALostArkClassPlayerController::CompletedSkill_S()
{
	if (IsActiveSkill)
	{
		if (currentSkillKey != ESkillIndex::S)
			return;

		if (currentSkillType == ESkillType::Charge || currentSkillType == ESkillType::Casting)
			ReleaseSkill.Execute();
	}
}
void ALostArkClassPlayerController::CompletedSkill_D()
{
	if (IsActiveSkill)
	{
		if (currentSkillKey != ESkillIndex::D)
			return;

		if (currentSkillType == ESkillType::Charge || currentSkillType == ESkillType::Casting)
			ReleaseSkill.Execute();
	}
}
void ALostArkClassPlayerController::CompletedSkill_F()
{
	if (IsActiveSkill)
	{
		if (currentSkillKey != ESkillIndex::F)
			return;

		if (currentSkillType == ESkillType::Charge || currentSkillType == ESkillType::Casting)
			ReleaseSkill.Execute();
	}
}

void ALostArkClassPlayerController::UseSkill(ABaseSkill* Skill)
{
	if (IsActiveSkill)
		return;

	if (Skill->IsReady)
	{
		if (IsPointingSkill)
		{
			CancelSkill.Execute();
			IsPointingSkill = false;
		}

		ESkillType type = Skill->SkillType;
		switch (type)
		{
		case ESkillType::Normal:
			IsActiveSkill = true;
			break;
		case ESkillType::Charge:
			IsActiveSkill = true;
			break;
		case ESkillType::Casting:
			IsActiveSkill = true;
			break;
		case ESkillType::Point:
			IsPointingSkill = true;
			break;
		default:
			break;
		}
		currentSkillType = Skill->SkillType;
		Skill->UseSkill();
	}
}

void ALostArkClassPlayerController::EndSkill(ABaseSkill* Skill)
{
	IsActiveSkill = false;
	previousSkill = Skill;
	currentSkillType = ESkillType::None;
}

void ALostArkClassPlayerController::ActiveAttack()
{
	if (IsPointingSkill)
	{
		bool IsSuccess = ActiveSkill.Execute();
		if (IsSuccess) 
		{
			IsPointingSkill = false;
		}
		
	}
	else
	{
		// 기본 공격
	}
}

