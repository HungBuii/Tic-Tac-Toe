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
	if (bIsPlayerTurn && !IsFullGrid())
	{
		if (Grid[Row][Col] == 0) // its empty 
		{
			Grid[Row][Col] = 1; // 1: represent the Player
			
			AMyPlayerPawn* MyPlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			MyPlayerPawn->MainBoardWidget->OnCellClicked(Row, Col, "X");
		}
		
		SwitchTurn();
	}
}

void ATicTacToeGameMode::SwitchTurn()
{
	bIsPlayerTurn = !bIsPlayerTurn;
	
	bool IsTimerAlreadyActive = GetWorldTimerManager().IsTimerActive(AITurnWaitTimer);
	if (IsTimerAlreadyActive) GetWorldTimerManager().ClearTimer(AITurnWaitTimer);
	GetWorldTimerManager().SetTimer(AITurnWaitTimer, this, &ATicTacToeGameMode::AIMove, 
		1.f, false, 1.f);
}

void ATicTacToeGameMode::AIMove()
{
	int Row = 0;
	int Col = 0;
	
	if (!IsFullGrid())
	{
		while (Grid[Row][Col] != 0) // can use do.while
		{
			Row = FMath::RandRange(0, 2);
			Col = FMath::RandRange(0, 2);
		}
		
		if (Grid[Row][Col] == 0)
		{
			Grid[Row][Col] = 2; // 2: represent the AI
			
			AMyPlayerPawn* MyPlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			MyPlayerPawn->MainBoardWidget->OnCellClicked(Row, Col, "O");
		}
		
		if (!bIsPlayerTurn)
		{
			bIsPlayerTurn = true;
		}
	}
}

bool ATicTacToeGameMode::IsFullGrid()
{
	for (int Row = 0; Row < 3; ++Row)
	{
		for (int Col = 0; Col < 3; ++Col)
		{
			if (Grid[Row][Col] == 0) return false;
		}
	}
	
	return true;
}
