// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurretCPP.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyTurretCPP::AEnemyTurretCPP()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyTurretCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyTurretCPP::AudioInteract_Implementation(AActor* _Instigator)
{
	//This is an optional call in case the function has an initial implementation
	IAudioInteract::AudioInteract_Implementation(_Instigator);

	if (bOnAlert) // If the turret in already on alert mode, return
	{
		return;
	}

	bOnAlert = true;

	// Add a debug message to the screen (Print String)
	GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
		TEXT("CPP: Audio Interact called on " + GetActorLabel() + " by " + _Instigator->GetActorLabel()));

	// Set the oscillation parameter on the Static Mesh current material
	StaticMeshComponent->SetScalarParameterValueOnMaterials(MaterialParamFX, MaterialParamOnAlertValue);

	if (IsValid(OnAlertSound))
	{
		// Play the sound and set it to stop after a set amount of seconds
		UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAttached(OnAlertSound, StaticMeshComponent);
		AudioComponent->StopDelayed(AlertRefreshTime);
	}

	/**
	 * IMPORTANT: For the purpose of showing how to extend this function in BP, I implemented the Delay -> Stop functionality
	 * in the child BP of this class.
	 * Delays and timers in C++ are not as straightforward as in BP and go beyond the scope of this project's objective.
	 */
}

// Called every frame
void AEnemyTurretCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


