// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Main.h"
#include "CP_Pawn_Sub_Character.h"
#include "CP_PC_Sub_Character.h"
#include "GameFramework/GameModeBase.h"
#include "CP_GM_Sub_Character.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MAIN_API ACP_GM_Sub_Character : public AGameModeBase
{
	GENERATED_BODY()
	
	ACP_GM_Sub_Character();

public:
	virtual void PostLogin(APlayerController* _NewPlayer) override;
};
