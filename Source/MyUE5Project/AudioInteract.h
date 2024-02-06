// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AudioInteract.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAudioInteract : public UInterface
{
	GENERATED_BODY()
};

class MYUE5PROJECT_API IAudioInteract
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	/**
	 * Calls the AudioInteract() on an Actor that implements this interface
	 * As a BlueprintNativeEvent, if defined in a C++ class, it requires a C++ implementation too (AudioInteract_Implementation)
	 * This C++ implementation can be extended or overriden in Blueprint
	 * @param _Instigator The actor that calls this function
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AudioInteract(AActor* _Instigator);
};
