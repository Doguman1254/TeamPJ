// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_GM_Sub_Character.h"
#include "CP_Character_Sub_Character.h"

ACP_GM_Sub_Character::ACP_GM_Sub_Character()
{
	DefaultPawnClass = ACP_Character_Sub_Character::StaticClass();
	PlayerControllerClass = ACP_PC_Sub_Character::StaticClass();
}

void ACP_GM_Sub_Character::PostLogin(APlayerController* _NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(_NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));
}
