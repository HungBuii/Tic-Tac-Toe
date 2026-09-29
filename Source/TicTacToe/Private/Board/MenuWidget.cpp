// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/MenuWidget.h"

#include "Board/Common/DifficultyButtonWidget.h"
#include "Components/CheckBox.h"
#include "Components/UniformGridPanel.h"

void UMenuWidget::GenerateDifficultyButton()
{
	for (int i = 0; i < 3; i++)
	{
		UDifficultyButtonWidget* NewDifficultyButton = CreateWidget<UDifficultyButtonWidget>(GetWorld(), 
			DifficultyButtonWidgetClass);

		if (NewDifficultyButton)
		{
			NewDifficultyButton->SetDifficultyText(DifficultyTextArray[i]);
		}
		
		if (SelectDifficultyButtonGrid)
		{
			SelectDifficultyButtonGrid->AddChildToUniformGrid(NewDifficultyButton,0, i);
		}
	}
}

bool UMenuWidget::CanPlayerGoFirst() const
{
	if (CB_GoFirst->IsChecked())
	{
		return true;
	}
	return false;
}
