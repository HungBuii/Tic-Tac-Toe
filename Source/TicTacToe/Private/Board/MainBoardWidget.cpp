// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/MainBoardWidget.h"

#include "Board/Common/CellBoardWidget.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"

int UMainBoardWidget::GetRow()
{
	return Row;
}

int UMainBoardWidget::GetCol()
{
	return Col;
}

void UMainBoardWidget::GenerateBoard()
{
	for (int tpRow = 0; tpRow < Row; tpRow++)
	{
		for (int tpCol = 0; tpCol < Col; tpCol++)
		{
			UCellBoardWidget* NewCell = CreateWidget<UCellBoardWidget>(GetWorld(), CellBoardWidgetClass);
			NewCell->SetCellRow(tpRow);
			NewCell->SetCellColumn(tpCol);
			NewCell->SetButtonMargin(tpRow, tpCol);
			NewCell->SetSymbolText("!");
			
			if (GridPanel)
			{
				GridPanel->AddChildToGrid(NewCell, tpRow, tpCol);
			}
			
			Cells.Add(NewCell);
		}
	}
}

void UMainBoardWidget::ChangeCellColor(int pRow, int pCol, int Id)
{
	int CellIndex = pRow * 3 + pCol;
	
	if (Cells.IsValidIndex(CellIndex))
	{
		if (Id == 1)
		{
			Cells[CellIndex]->GetSymbolText()->SetColorAndOpacity(FLinearColor::Green);
		}
		if (Id == 2)
		{
			Cells[CellIndex]->GetSymbolText()->SetColorAndOpacity(FLinearColor::Red);
		}
		
	}
}

void UMainBoardWidget::OnCellClicked(int pRow, int pCol, FString Symbol)
{
	int CellIndex = pRow * 3 + pCol;

	if (Cells.IsValidIndex(CellIndex))
	{
		Cells[CellIndex]->GetButtonClick()->SetIsEnabled(false);
		Cells[CellIndex]->SetSymbolText(Symbol);
	}
}

void UMainBoardWidget::DisableAllCells()
{
	for (UCellBoardWidget* Cell : Cells)
	{
		Cell->GetButtonClick()->SetIsEnabled(false);
	}
}

void UMainBoardWidget::ChangeTurnText(FString NewTurnText)
{
	FString Str = FString::Printf(TEXT("%s"), *NewTurnText);
	TurnText->SetText(FText::FromString(Str));
}
