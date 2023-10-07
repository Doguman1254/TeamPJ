// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Main.h"
#include "Animation/AnimInstance.h"
#include "CP_Sub_Character_AnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class PROJECT_MAIN_API UCP_Sub_Character_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UCP_Sub_Character_AnimInstance();
	virtual void NativeUpdateAnimation(float _DeltaSeconds) override;
	
	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 _NewSection);

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	void  SetDeadAnim() { IsDead = true; }

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	FName GetAttackMontageSectionName(int32 Section);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};
