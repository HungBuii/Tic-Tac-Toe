// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MyPlayerPawnController.h"

AMyPlayerPawnController::AMyPlayerPawnController()
{
}

void AMyPlayerPawnController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}
