// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainBoardWidget.generated.h"

class UCellBoardWidget;
class UGridPanel;
/**
 * 
 */
UCLASS()
class TICTACTOE_API UMainBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	/** Grid */
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGridPanel> GridPanel;
	
public:
	UFUNCTION(BlueprintCallable)
	void GenerateBoard();
	
private:
	/** Cell */
	UPROPERTY(EditDefaultsOnly, Category="UI", meta=(AllowPrivateAccess=true))
	TSubclassOf<UCellBoardWidget> CellBoardWidgetClass;
	
	TArray<UCellBoardWidget*> Cells;
	
public:
	void OnCellClicked(int Row, int Col, FString Symbol);
	
};
