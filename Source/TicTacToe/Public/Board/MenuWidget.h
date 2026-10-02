// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UCheckBox;
class UDifficultyButtonWidget;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class TICTACTOE_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void GenerateDifficultyButton();
	
	bool CanPlayerGoFirst() const;
	
private:
	/** Select Difficulty Button Grid */
	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* SelectDifficultyButtonGrid;
	
	/** Difficulty Button Widget Class */
	UPROPERTY(EditDefaultsOnly, Category="DifficultyButtonWidget Class", meta=(AllowPrivateAccess=true))
	TSubclassOf<UDifficultyButtonWidget> DifficultyButtonWidgetClass;

	TArray<FString> DifficultyTextArray = {TEXT("Easy"), TEXT("Hard"), TEXT("PvP")};
	
	UPROPERTY(meta=(BindWidget))
	UCheckBox* CB_GoFirst;
};
