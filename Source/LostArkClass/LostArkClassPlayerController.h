// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "LostArkClassPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FActiveSkillDeleGate);
DECLARE_DYNAMIC_DELEGATE(FEndSkillDeleGate);

class ABaseSkill;

enum class ESkillIndex
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

	bool isActiveSkill;
	ABaseSkill* currentSkill;
	ABaseSkill* previousSkill;

	TMap<ESkillIndex, ABaseSkill*> SelectedSkills;
public:
	ALostArkClassPlayerController();


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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ABaseSkill>> AllSkills;

	FActiveSkillDeleGate ActiveSkill;
	FEndSkillDeleGate EndSkill;

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

	UFUNCTION()
	void SetCurSkill(ABaseSkill* CurSkill);

	UFUNCTION()
	void ActiveAttack();
private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};


