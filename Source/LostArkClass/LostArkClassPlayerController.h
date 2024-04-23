// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "BaseSkill.h"
#include "Skill_Identity.h"
#include "LostArkClassPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FActiveSkillDeleGate);
DECLARE_DYNAMIC_DELEGATE(FSkillDeleGate);

class ABaseSkill;

UENUM(BlueprintType)
enum class ESkillIndex : uint8
{
	Q = 0,
	W,
	E,
	R,
	A,
	S,
	D,
	F,
	Count
};

UCLASS()
class ALostArkClassPlayerController : public APlayerController
{
	GENERATED_BODY()

	bool IsActiveSkill;
	bool IsPointingSkill;
	ESkillIndex currentSkillKey;
	ESkillType currentSkillType;

public:
	ALostArkClassPlayerController();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	ABaseSkill* previousSkill;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TMap<ESkillIndex, ABaseSkill*> SelectedSkills;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	ASkill_Identity* IdentitySkill;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;


	// Skill
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionSkill_Q;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionSkill_W;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionSkill_E;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionSkill_R;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionSkill_A;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionSkill_S;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionSkill_D;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionSkill_F;

	// Identity
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionIdentity_Z;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* SetActionIdentity_X;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ABaseSkill>> AllSkills;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASkill_Identity> Identity_Init;

	FActiveSkillDeleGate ActiveSkill;
	FSkillDeleGate ReleaseSkill;
	FSkillDeleGate CancelSkill;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	// Skill
	void UseSkill_Q();
	void UseSkill_W();
	void UseSkill_E();
	void UseSkill_R();
	void UseSkill_A();
	void UseSkill_S();
	void UseSkill_D();
	void UseSkill_F();

	void TriggeredSkill_Q();
	void TriggeredSkill_W();
	void TriggeredSkill_E();
	void TriggeredSkill_R();
	void TriggeredSkill_A();
	void TriggeredSkill_S();
	void TriggeredSkill_D();
	void TriggeredSkill_F();

	void CompletedSkill_Q();
	void CompletedSkill_W();
	void CompletedSkill_E();
	void CompletedSkill_R();
	void CompletedSkill_A();
	void CompletedSkill_S();
	void CompletedSkill_D();
	void CompletedSkill_F();

	//Identity
	void UseIdentity_Z();
	void UseIdentity_X();

	UFUNCTION()
	void UseSkill(ABaseSkill* Skill);

	UFUNCTION()
	void ActiveAttack();
private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed

public:

	UFUNCTION()
	void EndSkill(ABaseSkill* Skill);
};


