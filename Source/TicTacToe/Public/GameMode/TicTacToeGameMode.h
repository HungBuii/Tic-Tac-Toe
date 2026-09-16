// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public: 
	ATicTacToeGameMode();
	
protected:
	virtual void BeginPlay() override;
	

};
