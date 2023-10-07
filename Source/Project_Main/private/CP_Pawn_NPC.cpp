// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_NPC.h"
#include "CP_Character_Sub_Character.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ACP_Pawn_NPC::ACP_Pawn_NPC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	CollisionSphere->InitSphereRadius(250.f);
	RootComponent = CollisionSphere;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(CollisionSphere);


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_NPC(TEXT("/Game/TeamPJ/Characters/MESH_PC_01.MESH_PC_01"));
	if (SK_NPC.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_NPC.Object);
	}

	TextBox = CreateDefaultSubobject<UWidgetComponent>(TEXT("TEXTBOX"));
	TextBox->SetupAttachment(Mesh);

	TextBox->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	TextBox->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_TEXT(TEXT("/Game/TeamPJ/UI/NPC_Box.NPC_Box_C"));
	if (UI_TEXT.Succeeded())
	{
		TextBox->SetWidgetClass(UI_TEXT.Class);
		TextBox->SetDrawSize(FVector2D(200.f, 100.f));
	}
	TextBox->SetVisibility(false);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACP_Pawn_NPC::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ACP_Pawn_NPC::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACP_Pawn_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACP_Pawn_NPC::Talk()
{
	
}

// Called every frame
void ACP_Pawn_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsTalk) 
		TextBox->SetVisibility(true);
	else
		TextBox->SetVisibility(false);

}

// Called to bind functionality to input
void ACP_Pawn_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (IsTalk)
	{
		PlayerInputComponent->BindAction(TEXT("Talk"), EInputEvent::IE_Pressed, this, &ACP_Pawn_NPC::Talk);
	}
	else return;
}

void ACP_Pawn_NPC::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!IsTalk)
	{
		IsTalk = true;
	}
}

void ACP_Pawn_NPC::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (IsTalk)
	{
		IsTalk = false;
	}
}

