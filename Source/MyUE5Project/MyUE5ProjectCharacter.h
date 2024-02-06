// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyUE5ProjectCharacter.generated.h"

UCLASS(Blueprintable)
class AMyUE5ProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyUE5ProjectCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:

	// Footstep sound .uasset
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundBase* FootstepSound;

	/**
	 * Spawns footstep sounds attached to a bone or socket location
	 * @param Bone Bone or Socket Name
	 * @param InteractRadius Radius in game units
	 */
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void OnPlayFootstepCPP(FName Bone, float InteractRadius);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

