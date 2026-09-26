// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/Common/DifficultyButtonWidget.h"

#include "Components/TextBlock.h"

void UDifficultyButtonWidget::SetDifficultyText(FString NewDifficultyText)
{
	if (DifficultyText)
	{
		DifficultyText->SetText(FText::FromString(NewDifficultyText));
	}
}
