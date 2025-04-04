// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Controller/PlayerPlaneController.h"
#include "Player/PlayerPlaneState.h"


APlayerPlaneController::APlayerPlaneController()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Plane/Input/IMC_Plane.IMC_Plane'") };
		check(Asset.Object);

		IMC_Default = Asset.Object;
	}
}

void APlayerPlaneController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(IMC_Default, 0);
			}
		}
	}
}

void APlayerPlaneController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Look")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Look is disabled"));
	}

	//if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_LeftClick")))
	//{
	//	EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnLeftClick);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("IA_LeftClick is disabled"));
	//}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Boost")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ThisClass::OnSpeedUp);
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnSpeedReset);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Boost is disabled"));
	}
}

void APlayerPlaneController::OnLook(const FInputActionValue& InputActionValue)
{
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	AddYawInput(ActionValue.X);
	AddPitchInput(-ActionValue.Y);
}

void APlayerPlaneController::OnLeftClick(const FInputActionValue& InputActionValue)
{
	//공격 총알 ? / 자체 쿨?
	//UE_LOG(LogTemp, Warning, TEXT("OnLeftClick"));	
}

void APlayerPlaneController::Server_SetBoost_Implementation(bool bEnabled)
{
	if (!PlayerState)
	{
		return;
	}
	APlayerPlaneState* PlayerPlaneState = GetPlayerState<APlayerPlaneState>();
	if (PlayerPlaneState)
	{
		PlayerPlaneState->SetBoost(bEnabled);
	}
}


void APlayerPlaneController::OnSpeedUp(const FInputActionValue& InputActionValue)
{
	Server_SetBoost(true);
}
void APlayerPlaneController::OnSpeedReset(const FInputActionValue& InputActionValue)
{
	Server_SetBoost(false);
}
