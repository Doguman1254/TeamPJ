// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Main.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "CP_Pawn_Sub_Character.generated.h"

UCLASS()
class PROJECT_MAIN_API ACP_Pawn_Sub_Character : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACP_Pawn_Sub_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category=Collision)
	UCapsuleComponent* pCapsule;

	UPROPERTY(VisibleAnywhere, Category=Visual)
	USkeletalMeshComponent* pMesh;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	UFloatingPawnMovement* pMovement;

	UPROPERTY(VisibleAnywhere, Category=SpringArm)
	USpringArmComponent* pSpringArm;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	UCameraComponent* pCamera;

private:

	void UpDown(float _NewAxisValue);
	void LeftRight(float _NewAxisValue);
};
