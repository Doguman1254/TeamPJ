// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_ActorComp_Sub_Character.h"

// Sets default values for this component's properties
UCP_ActorComp_Sub_Character::UCP_ActorComp_Sub_Character()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCP_ActorComp_Sub_Character::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCP_ActorComp_Sub_Character::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

