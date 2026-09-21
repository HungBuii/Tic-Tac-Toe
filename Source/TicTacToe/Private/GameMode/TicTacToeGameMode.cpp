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
	
	HumanWinDelegate.AddDynamic(this, &ATicTacToeGameMode::HumanWin);
	AIWinDelegate.AddDynamic(this, &ATicTacToeGameMode::AIWin);
	DrawGameDelegate.AddDynamic(this, &ATicTacToeGameMode::DrawGame);
}

void ATicTacToeGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	AMyPlayerPawn* MyPlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (CheckPlayerWin(1))
	{
		bIsPlayerTurn = false;
		MyPlayerPawn->MainBoardWidget->DisableAllCells();
		HumanWinDelegate.Broadcast();
		// MyPlayerPawn->MainBoardWidget->ChangeTurnText("Player Won!");
	}
	else if (CheckPlayerWin(2))
	{
		bIsPlayerTurn = false;
		MyPlayerPawn->MainBoardWidget->DisableAllCells();
		AIWinDelegate.Broadcast();
	}
	else
	{
		if (IsFullGrid())
		{
			DrawGameDelegate.Broadcast();
		}
		else
		{
			if (bIsPlayerTurn)
			{
				MyPlayerPawn->MainBoardWidget->ChangeTurnText("Player Turn");
			}
			else MyPlayerPawn->MainBoardWidget->ChangeTurnText("AI Turn");
		}
	}
	
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
	bIsPlayerTurn = false;
	
	if (!CheckPlayerWin(1))
	{
		bool IsTimerAlreadyActive = GetWorldTimerManager().IsTimerActive(AITurnWaitTimer);
		if (IsTimerAlreadyActive) GetWorldTimerManager().ClearTimer(AITurnWaitTimer);
		GetWorldTimerManager().SetTimer(AITurnWaitTimer, this, &ATicTacToeGameMode::AIMove, 
			1.f, false, 1.f);
	}
	
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
