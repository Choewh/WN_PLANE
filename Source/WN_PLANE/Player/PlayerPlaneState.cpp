// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPlaneState.h"

APlayerPlaneState::APlayerPlaneState()
{
	bReplicates = true;
}

void APlayerPlaneState::SetBoost(bool InBoost)
{
	if (bBoost == InBoost) return;

	bBoost = InBoost;

}

void APlayerPlaneState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerPlaneState, bBoost);
}

void APlayerPlaneState::OnRep_Boost()
{
	UE_LOG(LogTemp, Warning, TEXT("bBoost replicated on client: %s"), bBoost ? TEXT("TRUE") : TEXT("FALSE"));
}
