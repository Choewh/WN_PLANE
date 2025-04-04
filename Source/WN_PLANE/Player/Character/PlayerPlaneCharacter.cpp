// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Character/PlayerPlaneCharacter.h"
#include "Player/PlayerPlaneState.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
//#include "Kismet/KismetSystemLibrary.h"
//#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPlaneCharacter::APlayerPlaneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
	SetReplicateMovement(true);

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->DefaultLandMovementMode = MOVE_Flying;
	MovementComponent->BrakingDecelerationFlying = 5000.f;

	UCapsuleComponent* PlayerCapsuleComponent = GetCapsuleComponent();
	PlayerCapsuleComponent->SetCapsuleSize(100.f, 150.f);
	PlayerCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
		StaticMeshComponent->SetupAttachment(RootComponent);

		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Plane/Plane.Plane'"));

		if (MeshAsset.Succeeded())
		{
			StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
		}
		StaticMeshComponent->SetIsReplicated(true);
	}

	{
		SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->SetRelativeLocation(FVector(-200.f, 0.f, 30.f));
		SpringArm->ProbeChannel = ECC_WorldStatic;
		SpringArm->TargetArmLength = 500.f;
		SpringArm->SocketOffset = FVector(-200.f, 0.f, 230.f);
		SpringArm->bUsePawnControlRotation = true;
	}

	{
		PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
		PlayerCamera->SetupAttachment(SpringArm);
		PlayerCamera->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
		PlayerCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm
	}
	//TEnumAsByte<EAutoReceiveInput::Type> tempAutoPossessPlayer(1);
	//AutoPossessPlayer = tempAutoPossessPlayer;
}

// Called when the game starts or when spawned
void APlayerPlaneCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPlaneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocallyControlled())
	{
		OnPlaneMove(); // 클라에서 직접 AddMovementInput 호출
	}
}

void APlayerPlaneCharacter::Server_OnPlaneMove_Implementation()
{
	// 서버에서 처리
	OnPlaneMove();
}

void APlayerPlaneCharacter::OnPlaneMove()
{
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(PlayerCamera->GetComponentRotation());
	
	if (!GetPlayerState()) { return; }

	APlayerPlaneState* PlayerPlaneState = Cast<APlayerPlaneState>(GetPlayerState());
	if (PlayerPlaneState->GetBoost())
	{
		GetCharacterMovement()->MaxFlySpeed = 2000.f;
		AddMovementInput(ForwardVector, PlayerPlaneState->GetSpeed());
	}
	else
	{
		GetCharacterMovement()->MaxFlySpeed = 600.f;
		AddMovementInput(ForwardVector, PlayerPlaneState->GetSpeed());
	}
}

// Called to bind functionality to input
void APlayerPlaneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

