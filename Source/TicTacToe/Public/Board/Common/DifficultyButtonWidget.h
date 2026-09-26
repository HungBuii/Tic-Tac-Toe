// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DifficultyButtonWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class TICTACTOE_API UDifficultyButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	/** Set Text */
	void SetDifficultyText(FString NewDifficultyText);
	
private:
	UFUNCTION()
	void OnButtonClicked();
	
private:
	/** Button */
	UPROPERTY(meta=(BindWidget))
	UButton* DifficultyButton;
	
	/** Text */
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DifficultyText;
};
