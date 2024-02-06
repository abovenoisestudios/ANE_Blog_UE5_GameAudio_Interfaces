// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUE5ProjectGameMode.h"
#include "MyUE5ProjectPlayerController.h"
#include "MyUE5ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyUE5ProjectGameMode::AMyUE5ProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMyUE5ProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}