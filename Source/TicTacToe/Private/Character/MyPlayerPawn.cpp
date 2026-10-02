// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyPlayerPawn.h"

#include "Blueprint/UserWidget.h"
#include "Board/MainBoardWidget.h"
#include "Board/MenuWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPlayerPawn::AMyPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UMenuWidget>(UGameplayStatics::GetPlayerController(GetWorld(),
			                                       0), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToPlayerScreen();
		}
	}

	PlayerWinDelegate.AddDynamic(this, &AMyPlayerPawn::HumanWin);
	AIWinDelegate.AddDynamic(this, &AMyPlayerPawn::AIWin);
	DrawGameDelegate.AddDynamic(this, &AMyPlayerPawn::DrawGame);
}

// Called every frame
void AMyPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AMyPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyPlayerPawn::CreateMainBoardWidget()
{
	if (MainBoardClass)
	{
		MainBoardWidget = CreateWidget<UMainBoardWidget>(UGameplayStatics::GetPlayerController(GetWorld(),
			                                                 0), MainBoardClass);
		if (MainBoardWidget)
		{
			MainBoardWidget->AddToPlayerScreen();
			bIsPlayerTurn = MenuWidget->CanPlayerGoFirst();
			bIsGameOver = false;
		}
	}

	if (!bIsPlayerTurn)
	{
		SwitchAITurn();
		MainBoardWidget->ChangeTurnText("AI Turn");
	}
	else
	{
		bIsPlayerTurn = true;
		MainBoardWidget->ChangeTurnText("Human Turn");
	}
}

void AMyPlayerPawn::PlayerMove(int Row, int Col)
{
	if (bIsPlayerTurn && !IsFullGrid() && !bIsGameOver)
	{
		if (Grid[Row][Col] == 0) // its empty 
		{
			Grid[Row][Col] = 1; // 1: represent the Player

			MainBoardWidget->OnCellClicked(Row, Col, "X");
			
			if (StatusGameUpdate(1)) return;
			
			MainBoardWidget->ChangeTurnText("AI Turn");

			bIsPlayerTurn = false;
			SwitchAITurn();
		}
	}
}

void AMyPlayerPawn::AIMove()
{
	if (!bIsPlayerTurn && !IsFullGrid() && !bIsGameOver)
	{
		int Row = FMath::RandRange(0, MainBoardWidget->GetRow() - 1);
		int Col = FMath::RandRange(0, MainBoardWidget->GetRow() - 1);
		while (Grid[Row][Col] != 0) // can use do.while
		{
			Row = FMath::RandRange(0, MainBoardWidget->GetRow() - 1);
			Col = FMath::RandRange(0, MainBoardWidget->GetRow() - 1);
		}
		if (Grid[Row][Col] == 0)
		{
			Grid[Row][Col] = 2; // 2: represent the AI

			MainBoardWidget->OnCellClicked(Row, Col, "O");
			
			if (StatusGameUpdate(2)) return;
			
			MainBoardWidget->ChangeTurnText("Human Turn");
			bIsPlayerTurn = true;
		}
	}
}

void AMyPlayerPawn::SwitchAITurn()
{
	// bool IsTimerAlreadyActive = GetWorldTimerManager().IsTimerActive(AITurnWaitTimer);
	// if (IsTimerAlreadyActive) GetWorldTimerManager().ClearTimer(AITurnWaitTimer);
	GetWorldTimerManager().SetTimer(AITurnWaitTimer, this, &AMyPlayerPawn::AIMove,
	                                1.f, false, 1.f);
}

bool AMyPlayerPawn::IsFullGrid() const
{
	for (int Row = 0; Row < MainBoardWidget->GetRow(); Row++)
	{
		for (int Col = 0; Col < MainBoardWidget->GetCol(); Col++)
		{
			if (Grid[Row][Col] == 0) return false;
		}
	}

	return true;
}

bool AMyPlayerPawn::CheckPlayerWin(int Id)
{
	// check row
	for (int i = 0; i < MainBoardWidget->GetRow(); i++)
	{
		Cells.Empty();
		for (int j = 0; j <= MainBoardWidget->GetCol() - 3; j++)
		{
			if (Grid[i][j] == Id && Grid[i][j + 1] == Id && Grid[i][j + 2] == Id)
			{
				Cells.Add(SelectedCell(i, j));
				Cells.Add(SelectedCell(i, j + 1));
				Cells.Add(SelectedCell(i, j + 2));
				return true;
			}
		}
	}

	// check column
	for (int i = 0; i <= MainBoardWidget->GetRow() - 3; i++)
	{
		Cells.Empty();
		for (int j = 0; j < MainBoardWidget->GetCol(); j++)
		{
			if (Grid[i][j] == Id && Grid[i + 1][j] == Id && Grid[i + 2][j] == Id)
			{
				Cells.Add(SelectedCell(i, j));
				Cells.Add(SelectedCell(i + 1, j));
				Cells.Add(SelectedCell(i + 2, j));
				return true;
			}
		}
	}

	// check "\"
	for (int i = 0; i < MainBoardWidget->GetRow(); i++)
	{
		Cells.Empty();
		for (int j = 0; j <= MainBoardWidget->GetCol() - 3; j++)
		{
			if (Grid[i][j] == Id && Grid[i + 1][j + 1] == Id && Grid[i + 2][j + 2] == Id)
			{
				Cells.Add(SelectedCell(i, j));
				Cells.Add(SelectedCell(i + 1, j + 1));
				Cells.Add(SelectedCell(i + 2, j + 2));
				return true;
			}
		}
	}

	// check "/"
	for (int i = 0; i <= MainBoardWidget->GetRow() - 3; i++)
	{
		Cells.Empty();
		for (int j = 2; j < MainBoardWidget->GetCol(); j++)
		{
			if (Grid[i][j] == Id && Grid[i + 1][j - 1] == Id && Grid[i + 2][j - 2] == Id)
			{
				Cells.Add(SelectedCell(i, j));
				Cells.Add(SelectedCell(i + 1, j - 1));
				Cells.Add(SelectedCell(i + 2, j - 2));
				return true;
			}
		}
	}

	return false;
}

void AMyPlayerPawn::HumanWin()
{
	MainBoardWidget->ChangeTurnText("Human Won!");
}

void AMyPlayerPawn::AIWin()
{
	MainBoardWidget->ChangeTurnText("AI Won!");
}

void AMyPlayerPawn::DrawGame()
{
	MainBoardWidget->ChangeTurnText("Draw!");
}

bool AMyPlayerPawn::StatusGameUpdate(int Id)
{
	if (CheckPlayerWin(Id) && Id == 1)
	{
		bIsGameOver = true;
		MainBoardWidget->DisableAllCells();
		PlayerWinDelegate.Broadcast();

		for (SelectedCell Cell : Cells)
		{
			MainBoardWidget->ChangeCellColor(Cell.Row, Cell.Col, Id);
		}
		return true;
	}
	if (CheckPlayerWin(Id) && Id == 2)
	{
		bIsGameOver = true;
		MainBoardWidget->DisableAllCells();
		AIWinDelegate.Broadcast();

		for (SelectedCell Cell : Cells)
		{
			MainBoardWidget->ChangeCellColor(Cell.Row, Cell.Col, Id);
		}
		return true;
	}
	if (IsFullGrid())
	{
		DrawGameDelegate.Broadcast();
		return true;
	}
	return false;
}
