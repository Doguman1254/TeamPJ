// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Actor_NPC.h"
#include "Components/WidgetComponent.h"

// Sets default values
ACP_Actor_NPC::ACP_Actor_NPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ACP_Actor_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACP_Actor_NPC::NotifyActorBeginOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("Start"));
}

void ACP_Actor_NPC::NotifyActorEndOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("End"));
}

void ACP_Actor_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



