// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_Sub_Character.h"

// Sets default values
ACP_Pawn_Sub_Character::ACP_Pawn_Sub_Character()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	pMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	pMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVE"));
	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = pCapsule;
	pMesh->SetupAttachment(pCapsule);
	pSpringArm->SetupAttachment(pCapsule);
	pCamera->SetupAttachment(pSpringArm);

	pCapsule->SetCapsuleHalfHeight(88.0f);
	pCapsule->SetCapsuleRadius(34.0f);
	pMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.0f), FRotator(0.f, -90.f, 0.f));
	pSpringArm->TargetArmLength = 400.0f;
	pSpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Yin(TEXT("/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin"));
	if (SK_Yin.Succeeded())
	{
		pMesh->SetSkeletalMesh(SK_Yin.Object);
	}

	pMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> Yin_ANIM(TEXT("/Game/TeamPJ/Animations/NewAnimBlueprint.NewAnimBlueprint_C"));
	if (Yin_ANIM.Succeeded())
	{
		pMesh->SetAnimInstanceClass(Yin_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void ACP_Pawn_Sub_Character::BeginPlay()
{
	Super::BeginPlay();
	/*pMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/ParagonYin/Characters/Heroes/Yin/Animations/Jog_Fwd.Jog_Fwd"));
	if (AnimAsset != nullptr)
	{
		pMesh->PlayAnimation(AnimAsset, true);
	}*/
}

// Called every frame
void ACP_Pawn_Sub_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACP_Pawn_Sub_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ACP_Pawn_Sub_Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ACP_Pawn_Sub_Character::LeftRight);
}
void ACP_Pawn_Sub_Character::UpDown(float _NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), _NewAxisValue);
}

void ACP_Pawn_Sub_Character::LeftRight(float _NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), _NewAxisValue);
}


void ACP_Pawn_Sub_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void ACP_Pawn_Sub_Character::PossessedBy(AController* NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}

