// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Main.h"
#include "GameFramework/PlayerController.h"
#include "CP_PC_Sub_Character.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MAIN_API ACP_PC_Sub_Character : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
};
