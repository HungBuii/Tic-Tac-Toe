// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/CellBoardWidget.h"

#include "IPropertyTable.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode/GameModeInterface.h"
#include "GameMode/TicTacToeGameMode.h"
#include "Kismet/GameplayStatics.h"

void UCellBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonClick)
	{
		ButtonClick->OnClicked.AddDynamic(this, &UCellBoardWidget::OnButtonClicked);
	}
}

void UCellBoardWidget::SetCellRow(int Row)
{
	CellRow = Row;
}

void UCellBoardWidget::SetCellColumn(int Column)
{
	CellColumn = Column;
}

void UCellBoardWidget::SetButtonMargin(int Row, int Col)
{
	if (ButtonClick)
	{
		FMargin Margin = FMargin(1.f, 1.f, 1.f, 1.f);
		
		if (Col == 0)
		{
			Margin.Left = 0.f;
		}
		else if (Col == 2)
		{
			Margin.Right = 0.f;
		}
		
		if (Row == 0)
		{
			Margin.Top = 0.f;
		}
		else if (Row == 2)
		{
			Margin.Bottom = 0.f;
		}
		
		FButtonStyle NewButtonStyle = ButtonClick->WidgetStyle;
		NewButtonStyle.Normal.Margin = Margin;
		NewButtonStyle.Hovered.Margin = Margin;
		NewButtonStyle.Pressed.Margin = Margin;
		ButtonClick->SetStyle(NewButtonStyle);
	}
}

void UCellBoardWidget::OnButtonClicked()
{
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	if (GameMode && GameMode->GetClass()->ImplementsInterface(UGameModeInterface::StaticClass()))
	{
		IGameModeInterface* GameModeInterface = Cast<IGameModeInterface>(GameMode);
		
		if (GameModeInterface)
		{
			GameModeInterface->GetTicTacToeGameMode()->PlayerMove(CellRow, CellColumn);
		}
	}
}

void UCellBoardWidget::SetSymbolText(FString SymbolText)
{
	if (Symbol)
	{
		Symbol->SetText(FText::FromString(SymbolText));
	}
}
