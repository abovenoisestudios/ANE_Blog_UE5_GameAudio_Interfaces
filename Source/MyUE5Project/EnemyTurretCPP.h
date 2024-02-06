// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioInteract.h"
#include "GameFramework/Actor.h"
#include "EnemyTurretCPP.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MYUE5PROJECT_API AEnemyTurretCPP : public AActor, public IAudioInteract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyTurretCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Turret CPP")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy Turret CPP")
	bool bOnAlert = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy Turret CPP")
	USoundBase* OnAlertSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy Turret CPP")
	FName MaterialParamFX = "OscMultiplier";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy Turret CPP")
	float MaterialParamOnAlertValue = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy Turret CPP")
	float AlertRefreshTime = 10.f;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AudioInteract(AActor* _Instigator);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
