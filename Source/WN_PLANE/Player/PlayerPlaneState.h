// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerPlaneState.generated.h"

/**
 * 
 */
UCLASS()
class WN_PLANE_API APlayerPlaneState : public APlayerState
{
	GENERATED_BODY()
	

public:

	void SetBoost(bool InBoost);

	float GetSpeed() { return Speed; }
	float GetBonusSpeed() { return BonusSpeed; }
	float GetBoost() { return bBoost; }


private:

	float Speed = 1.f;
	float BonusSpeed = 1.f;
	bool bBoost = false;
};
