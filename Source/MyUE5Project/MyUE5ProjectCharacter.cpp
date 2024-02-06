// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUE5ProjectCharacter.h"

#include "AudioInteract.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AMyUE5ProjectCharacter::AMyUE5ProjectCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyUE5ProjectCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AMyUE5ProjectCharacter::OnPlayFootstepCPP(FName Bone, float InteractRadius)
{
	// Spawns and plays a USoundBase sound asset
	UGameplayStatics::SpawnSoundAttached(FootstepSound, GetMesh(), Bone);

	const FVector BoneLocation = GetMesh()->GetSocketLocation(Bone); // Gets the bone or socket location
	TArray<FHitResult> Hits; // Array of Hit Results allocated by the SphereTraceMulti() function

	// This function traces a sphere around the provided location and stores all the actors it hits within its radius
	const bool bHit = UKismetSystemLibrary::SphereTraceMulti(this, BoneLocation, BoneLocation, InteractRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),false, {},
		EDrawDebugTrace::ForDuration, Hits,true,  FLinearColor::Red, FLinearColor::Green, 1.f);

	if (!bHit) // If the sphere didn't hit anything, return
	{
		return;
	}

	for (FHitResult& Hit : Hits)
	{
		// For every HitResult, check if the actor in the struct implements the IAudioInteract interface
		if (Hit.GetActor()->GetClass()->ImplementsInterface(UAudioInteract::StaticClass()))
		{
			// If it does, execute the AudioInteract() function on the actor.
			IAudioInteract::Execute_AudioInteract(Hit.GetActor(), this);
		}
	}
}



