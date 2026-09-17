// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerPawnController.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API AMyPlayerPawnController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerPawnController();
	
protected:
	virtual void BeginPlay() override;
};
