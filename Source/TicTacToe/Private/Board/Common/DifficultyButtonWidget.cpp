// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/Common/DifficultyButtonWidget.h"

#include "Character/MyPlayerPawn.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UDifficultyButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (DifficultyButton)
	{
		DifficultyButton->OnClicked.AddDynamic(this, &UDifficultyButtonWidget::OnButtonClicked);
	}
}

void UDifficultyButtonWidget::SetDifficultyText(FString NewDifficultyText)
{
	if (DifficultyText)
	{
		DifficultyText->SetText(FText::FromString(NewDifficultyText));
	}
}

void UDifficultyButtonWidget::OnButtonClicked()
{
	if (DifficultyText->GetText().EqualTo(FText::FromString("Easy")))
	{
		AMyPlayerPawn* PlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn
				(GetWorld(), 0));
		if (PlayerPawn)
		{
			// Create MainBoardWidget
			PlayerPawn->CreateMainBoardWidget("Easy");
		}
	}
	
	if (DifficultyText->GetText().EqualTo(FText::FromString("Hard")))
	{
		AMyPlayerPawn* PlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn
				(GetWorld(), 0));
		if (PlayerPawn)
		{
			// Create MainBoardWidget
			PlayerPawn->CreateMainBoardWidget("Hard");
		}
	}
	
	if (DifficultyText->GetText().EqualTo(FText::FromString("PvP")))
	{
		AMyPlayerPawn* PlayerPawn = Cast<AMyPlayerPawn>(UGameplayStatics::GetPlayerPawn
				(GetWorld(), 0));
		if (PlayerPawn)
		{
			// Create MainBoardWidget
			PlayerPawn->CreateMainBoardWidget("PvP");
		}
	}
}
