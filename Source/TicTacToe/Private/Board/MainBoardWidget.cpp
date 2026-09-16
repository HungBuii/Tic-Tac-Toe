// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/MainBoardWidget.h"

#include "Board/CellBoardWidget.h"
#include "Components/GridPanel.h"

void UMainBoardWidget::GenerateBoard()
{
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Col = 0; Col < 3; Col++)
		{
			UCellBoardWidget* NewCell = CreateWidget<UCellBoardWidget>(GetWorld(), CellBoardWidgetClass);
			
			if (GridPanel)
			{
				GridPanel->AddChildToGrid(NewCell, Row, Col);
			}
			
			Cells.Add(NewCell);
		}
	}
}
