// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPlaneState.h"

void APlayerPlaneState::SetBoost(bool InBoost)
{
	if (bBoost == InBoost) return;

	bBoost = InBoost;

}