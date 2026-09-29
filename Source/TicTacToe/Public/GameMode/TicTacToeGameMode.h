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
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
};
