// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlaneGameMode.h"
#include "Player/Controller/PlayerPlaneController.h"
#include "Player/Character/PlayerPlaneCharacter.h"
#include "Player/PlayerPlaneState.h"
#include "PlaneGameMode.h"

APlaneGameMode::APlaneGameMode()
{
		DefaultPawnClass = APlayerPlaneCharacter::StaticClass();
		PlayerControllerClass = APlayerPlaneController::StaticClass();
		PlayerStateClass = APlayerPlaneState::StaticClass();
}
