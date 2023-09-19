// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Character_Sub_Character.h"

// Sets default values
ACP_Character_Sub_Character::ACP_Character_Sub_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	pSpringArm->SetupAttachment(GetCapsuleComponent());
	pCamera->SetupAttachment(pSpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f,-90.f,0.f));
	pSpringArm->TargetArmLength = 400.f;
	pSpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Yin(TEXT("/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin"));
	if (SK_Yin.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Yin.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> YIN_ANIM(TEXT("/Game/TeamPJ/Animations/NewAnimBlueprint.NewAnimBlueprint_C"));
	if (YIN_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(YIN_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void ACP_Character_Sub_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACP_Character_Sub_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACP_Character_Sub_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ACP_Character_Sub_Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ACP_Character_Sub_Character::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACP_Character_Sub_Character::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACP_Character_Sub_Character::Turn);
}

void ACP_Character_Sub_Character::UpDown(float _NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), _NewAxisValue);
}

void ACP_Character_Sub_Character::LeftRight(float _NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), _NewAxisValue);
}

void ACP_Character_Sub_Character::Turn(float _NewAxisValue)
{
	AddControllerYawInput(_NewAxisValue);
}

void ACP_Character_Sub_Character::LookUp(float _NewAxisValue)
{
	AddControllerPitchInput(_NewAxisValue);
}

