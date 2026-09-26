// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyPlayerPawn.h"

#include "Blueprint/UserWidget.h"
#include "Board/MainBoardWidget.h"
#include "Board/MenuWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPlayerPawn::AMyPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (MenuWidgetClass)	
	{
		MenuWidget = CreateWidget<UMenuWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 
			0), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToPlayerScreen();
		}
	}
}

// Called every frame
void AMyPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPlayerPawn::CreateMainBoardWidget()
{
	if (MainBoardHUDClass)	
	{
		MainBoardWidget = CreateWidget<UMainBoardWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 
			0), MainBoardHUDClass);
		if (MainBoardWidget)
		{
			MainBoardWidget->AddToPlayerScreen();
		}
	}
}

