// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CellBoardWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class TICTACTOE_API UCellBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
private:
	/** Row, Column variable */
	int CellRow;
	int CellColumn;
	
public:
	void SetCellRow(int Row);
	void SetCellColumn(int Column);
	
private:
	/** Button */
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ButtonClick;
	
public:
	void SetButtonMargin(int Row, int Col);
	
private:
	UFUNCTION()
	void OnButtonClicked();
	
	/** Symbol Text */
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Symbol;
	
public:
	void SetSymbolText(FString SymbolText);
};
