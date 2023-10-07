// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Main.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "CP_Pawn_NPC.generated.h"

UCLASS()
class PROJECT_MAIN_API ACP_Pawn_NPC : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACP_Pawn_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Talk();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsTalk;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* TextBox;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* CommuBox;
};
