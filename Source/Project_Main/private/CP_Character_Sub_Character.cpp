// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Character_Sub_Character.h"
#include "CP_Sub_Character_AnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

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

	SetControlMode(0);
	GetCharacterMovement()->JumpZVelocity = 600.0f;

	IsAttacking = false;

	MaxCombo = 4;
	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("SubCharacter"));

	AttackRange = 200.f;
	AttackRadius = 50.f;
}

// Called when the game starts or when spawned
void ACP_Character_Sub_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACP_Character_Sub_Character::SetControlMode(int32 _ControlMode)
{
	if (_ControlMode == 0)
	{
		pSpringArm->TargetArmLength = 450.0f;
		pSpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		pSpringArm->bUsePawnControlRotation = true;
		pSpringArm->bInheritPitch = true;
		pSpringArm->bInheritRoll = true;
		pSpringArm->bInheritYaw = true;
		pSpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 720.0f, 0.f);
	}
}

// Called every frame
void ACP_Character_Sub_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACP_Character_Sub_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ACPAnim = Cast<UCP_Sub_Character_AnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(nullptr != ACPAnim);

	ACPAnim->OnMontageEnded.AddDynamic(this, &ACP_Character_Sub_Character::OnAttackMontageEnded);

	ACPAnim->OnNextAttackCheck.AddLambda([this]()-> void {
		ABLOG(Warning, TEXT("OnNextAttackCheck"));
		CanNextCombo = false;

		if (IsComboInputOn)
		{
			AttackStartComboState();
			ACPAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	});

	ACPAnim->OnAttackHitCheck.AddUObject(this, &ACP_Character_Sub_Character::AttackCheck);
}

float ACP_Character_Sub_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	if (FinalDamage > 0.0f)
	{
		ACPAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	}

	return FinalDamage;
}

// Called to bind functionality to input
void ACP_Character_Sub_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,this, &ACP_Character_Sub_Character::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed,this, &ACP_Character_Sub_Character::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ACP_Character_Sub_Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ACP_Character_Sub_Character::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACP_Character_Sub_Character::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACP_Character_Sub_Character::Turn);

}

void ACP_Character_Sub_Character::UpDown(float _NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), _NewAxisValue);
}

void ACP_Character_Sub_Character::LeftRight(float _NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), _NewAxisValue);
}

void ACP_Character_Sub_Character::Turn(float _NewAxisValue)
{
	AddControllerYawInput(_NewAxisValue);
}

void ACP_Character_Sub_Character::LookUp(float _NewAxisValue)
{
	AddControllerPitchInput(_NewAxisValue);
}

void ACP_Character_Sub_Character::Attack()
{
	if (IsAttacking)
	{
		ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		ABCHECK(CurrentCombo == 0);
		AttackStartComboState();
		ACPAnim->PlayAttackMontage();
		ACPAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void ACP_Character_Sub_Character::OnAttackMontageEnded(UAnimMontage* _Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	ABCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
}

void ACP_Character_Sub_Character::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ACP_Character_Sub_Character::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void ACP_Character_Sub_Character::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif //

	if (bResult)
	{
		if (HitResult.GetActor())
		{
			ABLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.GetActor()->GetName());
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(50.0f, DamageEvent, GetController(), this);
		}
	}
}

