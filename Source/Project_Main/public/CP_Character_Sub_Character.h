// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Main.h"
#include "GameFramework/Character.h"
#include "CP_Character_Sub_Character.generated.h"

UCLASS()
class PROJECT_MAIN_API ACP_Character_Sub_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACP_Character_Sub_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category=SpringArm)
	USpringArmComponent* pSpringArm;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	UCameraComponent* pCamera;

private:
	void UpDown(float _NewAxisValue);
	void LeftRight(float _NewAxisValue);
	void Turn(float _NewAxisValue);
	void LookUp(float _NewAxisValue);
};
