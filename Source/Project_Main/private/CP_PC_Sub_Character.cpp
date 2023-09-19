// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_PC_Sub_Character.h"

void ACP_PC_Sub_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void ACP_PC_Sub_Character::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(aPawn);
}
