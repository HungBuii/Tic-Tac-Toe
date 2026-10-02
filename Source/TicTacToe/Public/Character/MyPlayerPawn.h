// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayerPawn.generated.h"

class UMenuWidget;
class UMainBoardWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerWinDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIWinDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDrawGameDelegate);

struct SelectedCell
{
	int Row;
	int Col;
};

UCLASS()
class TICTACTOE_API AMyPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayerPawn();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	/** Create Widget "MainBoardWidget" */
	void CreateMainBoardWidget();
	
	/** Main Board */
	UPROPERTY(VisibleAnywhere, Category = "HUD", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMainBoardWidget> MainBoardWidget;
	
	/** Menu */
	UPROPERTY(VisibleAnywhere, Category = "HUD", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMenuWidget> MenuWidget;
	
	/** Player Turn */
	void PlayerMove(int Row, int Col);
	
	/** AI Turn */
	void AIMove();
	
	void SwitchAITurn();
	
	/** check grid is full? */
	bool IsFullGrid() const;
	
	/** check win/lose/draw */
	bool CheckPlayerWin(int Id);
	
	FPlayerWinDelegate PlayerWinDelegate;
	FAIWinDelegate AIWinDelegate;
	FDrawGameDelegate DrawGameDelegate;
	
	UFUNCTION()
	void HumanWin();
	
	UFUNCTION()
	void AIWin();
	
	UFUNCTION()
	void DrawGame();
	
	/** status game when check win/lose/draw */
	bool StatusGameUpdate(int Id);
	
private:
	/** Main Board */
	UPROPERTY(EditDefaultsOnly, Category = "HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<UMainBoardWidget> MainBoardClass;
	
	/** Menu */
	UPROPERTY(EditDefaultsOnly, Category = "HUD", meta=(AllowPrivateAccess=true))
	TSubclassOf<UMenuWidget> MenuWidgetClass;

private:
	/** Player Turn */
	UPROPERTY(EditAnywhere, Category="Select Turn Play", meta = (AllowPrivateAccess = "true"))
	bool bIsPlayerTurn = false;
	
	/** AI Turn */
	
	FTimerHandle AITurnWaitTimer;
	
	/** definition board 3x3 */
	int Grid[3][3];
	
	/** game over? */
	bool bIsGameOver = false;
	
	/** Archive selected cells */
	TArray<SelectedCell> Cells;
	
};
