// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"
#include "PlayerPlaneController.generated.h"

/**
 * 
 */
UCLASS()
class WN_PLANE_API APlayerPlaneController : public APlayerController
{
	GENERATED_BODY()

	APlayerPlaneController();

protected:
		
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(Server, Reliable)
	void Server_SetBoost(bool bEnabled);

protected:
	void OnLook(const FInputActionValue& InputActionValue);
	void OnLeftClick(const FInputActionValue& InputActionValue);
	void OnSpeedUp(const FInputActionValue& InputActionValue);
	void OnSpeedReset(const FInputActionValue& InputActionValue);

protected:

	UInputMappingContext* IMC_Default = nullptr;
};
