// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerPlaneState.generated.h"

/**
 * 
 */
UCLASS()
class WN_PLANE_API APlayerPlaneState : public APlayerState
{
	GENERATED_BODY()
	
	APlayerPlaneState();

public:
	UFUNCTION()
	void SetBoost(bool InBoost);
	UFUNCTION()
	float GetSpeed() { return Speed; }
	UFUNCTION()
	float GetBonusSpeed() { return BonusSpeed; }
	UFUNCTION()
	float GetBoost() { return bBoost; }
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void OnRep_Boost();

private:

	UPROPERTY(Replicated)
	float Speed = 1.f;
	UPROPERTY(Replicated)
	float BonusSpeed = 1.f;

	UPROPERTY(ReplicatedUsing = OnRep_Boost)
	bool bBoost = false;
};
