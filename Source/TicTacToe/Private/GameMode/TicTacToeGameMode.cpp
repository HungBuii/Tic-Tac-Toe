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
	
	Player1WinDelegate.AddDynamic(this, &ATicTacToeGameMode::HumanWin);
	AIWinDelegate.AddDynamic(this, &ATicTacToeGameMode::AIWin);
	DrawGameDelegate.AddDynamic(this, &ATicTacToeGameMode::DrawGame);
}

void ATicTacToeGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// AMyPlayerPawn* MyPlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//
	// if (CheckPlayerWin(1))
	// {
	// 	bIsPlayer1Turn = false;
	// 	MyPlayerPawn->MainBoardWidget->DisableAllCells();
	// 	Player1WinDelegate.Broadcast();
	// 	// MyPlayerPawn->MainBoardWidget->ChangeTurnText("Player Won!");
	// }
	// else if (CheckPlayerWin(2))
	// {
	// 	bIsPlayer1Turn = false;
	// 	MyPlayerPawn->MainBoardWidget->DisableAllCells();
	// 	AIWinDelegate.Broadcast();
	// }
	// else
	// {
	// 	if (IsFullGrid())
	// 	{
	// 		DrawGameDelegate.Broadcast();
	// 	}
	// 	else
	// 	{
	// 		if (bIsPlayer1Turn)
	// 		{
	// 			MyPlayerPawn->MainBoardWidget->ChangeTurnText("Player Turn");
	// 		}
	// 		else MyPlayerPawn->MainBoardWidget->ChangeTurnText("AI Turn");
	// 	}
	// }
	
}

void ATicTacToeGameMode::PlayerMove()
{
	if (bIsPlayer1Turn && !bIsAITurn && !IsFullGrid())
	{
		if (Grid[RowPlayer1Turn][ColPlayer1Turn] == 0) // its empty 
		{
			Grid[RowPlayer1Turn][ColPlayer1Turn] = 1; // 1: represent the Player
			
			AMyPlayerPawn* MyPlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			MyPlayerPawn->MainBoardWidget->OnCellClicked(RowPlayer1Turn, ColPlayer1Turn, "X");
		}
		
		bIsPlayer1Turn = false;
		bIsAITurn = true;
		SwitchTurn();
	}
}

void ATicTacToeGameMode::ButtonClicked(int Row, int Col)
{
	RowPlayer1Turn = Row;
	ColPlayer1Turn = Col;
}

void ATicTacToeGameMode::SwitchTurn()
{
	// if (!CheckPlayerWin(1) || !CheckPlayerWin(2))
	// {
	// 	if (bIsPlayer1Turn && !bIsAITurn)
	// 	{
	// 		PlayerMove();
	// 	}
	// 	if (!bIsPlayer1Turn && bIsAITurn)
	// 	{
	// 		bool IsTimerAlreadyActive = GetWorldTimerManager().IsTimerActive(AITurnWaitTimer);
	// 		if (IsTimerAlreadyActive) GetWorldTimerManager().ClearTimer(AITurnWaitTimer);
	// 		GetWorldTimerManager().SetTimer(AITurnWaitTimer, this, &ATicTacToeGameMode::AIMove, 
	// 			1.f, false, 1.f);
	// 	}
	// }
	
	if (bIsPlayer1Turn && !bIsAITurn)
	{
		if (!CheckPlayerWin(1) || !CheckPlayerWin(2)) PlayerMove();
	}
	
	if (!bIsPlayer1Turn && bIsAITurn)
	{
		if (!CheckPlayerWin(1) || !CheckPlayerWin(2))
		{
			bool IsTimerAlreadyActive = GetWorldTimerManager().IsTimerActive(AITurnWaitTimer);
			if (IsTimerAlreadyActive) GetWorldTimerManager().ClearTimer(AITurnWaitTimer);
			GetWorldTimerManager().SetTimer(AITurnWaitTimer, this, &ATicTacToeGameMode::AIMove, 
				1.f, false, 1.f);
		}
	}
}

void ATicTacToeGameMode::AIMove()
{
	int Row = 0;
	int Col = 0;
	
	if (!bIsPlayer1Turn && bIsAITurn && !IsFullGrid())
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
		
		bIsPlayer1Turn = true;
		bIsAITurn = false;
		SwitchTurn();
	}
}

bool ATicTacToeGameMode::IsFullGrid() const
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

bool ATicTacToeGameMode::CheckPlayerWin(int Id) const
{
	for (int i = 0; i < 3; i++) // check row
	{
		int count = 0;
		for (int j = 0; j < 3; j++)
		{
			if (Grid[i][j] == Id) count++;
			
			if (count == 3) return true;
		}
	}
	
	for (int i = 0; i < 3; i++) // check column
	{
		int count = 0;
		for (int j = 0; j < 3; j++)
		{
			if (Grid[j][i] == Id) count++;
			
			if (count == 3) return true;
		}
	}
	
	if (Grid[0][0] == Id && Grid[1][1] == Id && Grid[2][2] == Id) return true;
	if (Grid[0][2] == Id && Grid[1][1] == Id && Grid[2][0] == Id) return true;
	
	return false;
}

void ATicTacToeGameMode::HumanWin()
{
	AMyPlayerPawn* MyPlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	MyPlayerPawn->MainBoardWidget->ChangeTurnText("Human Won!");
}

void ATicTacToeGameMode::AIWin()
{
	AMyPlayerPawn* MyPlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	MyPlayerPawn->MainBoardWidget->ChangeTurnText("AI Won!");
}

void ATicTacToeGameMode::DrawGame()
{
	AMyPlayerPawn* MyPlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	MyPlayerPawn->MainBoardWidget->ChangeTurnText("Draw!");
}
