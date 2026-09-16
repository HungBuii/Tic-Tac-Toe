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
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ButtonClick;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Symbol;
};
