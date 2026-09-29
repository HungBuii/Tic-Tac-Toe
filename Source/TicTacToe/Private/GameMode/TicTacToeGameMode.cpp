// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TicTacToeGameMode.h"

#include "Board/MainBoardWidget.h"
#include "Character/MyPlayerPawn.h"
#include "Kismet/GameplayStatics.h"

ATicTacToeGameMode::ATicTacToeGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATicTacToeGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATicTacToeGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	
}

