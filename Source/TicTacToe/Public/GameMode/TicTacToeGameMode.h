// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToeGameMode : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()
	
public: 
	ATicTacToeGameMode();
	
	/** Get GameMode */
	virtual ATicTacToeGameMode* GetTicTacToeGameMode() override { return this; }
	
protected:
	virtual void BeginPlay() override;
	
private:
	/** Player Turn */
	bool bIsPlayerTurn = true;
	
public:
	void PlayerMove(int Row, int Col);
	
	void SwitchTurn();
	
	/** AI Turn */
	void AIMove();
	
private:
	/** definition board 3x3 */
	int Grid[3][3];
	
public:
	/** check grid is full? */
	bool IsFullGrid();
	
};
