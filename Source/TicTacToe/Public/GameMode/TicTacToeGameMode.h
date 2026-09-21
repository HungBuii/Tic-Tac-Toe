// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHumanWinDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIWinDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDrawGameDelegate);

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
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
private:
	/** Player Turn */
	bool bIsPlayerTurn = true;
	
public:
	void PlayerMove(int Row, int Col);
	
	void SwitchTurn();
	
	/** AI Turn */
private: 
	FTimerHandle AITurnWaitTimer;
		
public:
	void AIMove();
	
private:
	/** definition board 3x3 */
	int Grid[3][3];
	
public:
	/** check grid is full? */
	bool IsFullGrid() const;
	
	/** check win/lose/draw */
	bool CheckPlayerWin(int Id) const;
	
	FHumanWinDelegate HumanWinDelegate;
	FAIWinDelegate AIWinDelegate;
	FDrawGameDelegate DrawGameDelegate;
	
	UFUNCTION()
	void HumanWin();
	
	UFUNCTION()
	void AIWin();
	
	UFUNCTION()
	void DrawGame();
};
