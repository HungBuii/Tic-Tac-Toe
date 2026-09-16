// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TicTacToeGameMode.h"

#include "Board/MainBoardWidget.h"
#include "Character/MyPlayerPawn.h"
#include "Kismet/GameplayStatics.h"

ATicTacToeGameMode::ATicTacToeGameMode()
{
}

void ATicTacToeGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATicTacToeGameMode::PlayerMove(int Row, int Col)
{
	if (bIsPlayerTurn)
	{
		if (Grid[Row][Col] == 0) // its empty 
		{
			Grid[Row][Col] = 1; // 1: represent the player
			
			AMyPlayerPawn* MyPlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			MyPlayerPawn->MainBoardWidget->OnCellClicked(Row, Col, "X");
		}
	}
}
