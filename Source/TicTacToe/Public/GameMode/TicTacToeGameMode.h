// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayer1WinDelegate);
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
	UPROPERTY(EditAnywhere, Category="Select Turn Play", meta = (AllowPrivateAccess = "true"))
	bool bIsPlayer1Turn = false;
	
	int RowPlayer1Turn = 0;
	int ColPlayer1Turn = 0;
	
	/** AI Turn */
	UPROPERTY(EditAnywhere, Category="Select Turn Play", meta = (AllowPrivateAccess = "true"))
	bool bIsAITurn = false;
	
	FTimerHandle AITurnWaitTimer;
	
	/** definition board 3x3 */
	int Grid[3][3];
	
public:
	/** Player Turn */
	void PlayerMove();
	
	void ButtonClicked(int Row, int Col);
	
	/** AI Turn */
	void AIMove();
	
	void SwitchTurn();
	
public:
	/** check grid is full? */
	bool IsFullGrid() const;
	
	/** check win/lose/draw */
	bool CheckPlayerWin(int Id) const;
	
	FPlayer1WinDelegate Player1WinDelegate;
	FAIWinDelegate AIWinDelegate;
	FDrawGameDelegate DrawGameDelegate;
	
	UFUNCTION()
	void HumanWin();
	
	UFUNCTION()
	void AIWin();
	
	UFUNCTION()
	void DrawGame();
};
