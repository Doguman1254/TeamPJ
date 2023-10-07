// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Main.h"
#include "CP_GM_Sub_Character.h"
#include "GameFramework/Actor.h"
#include "CP_Actor_NPC.generated.h"

UCLASS()
class PROJECT_MAIN_API ACP_Actor_NPC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACP_Actor_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
};
