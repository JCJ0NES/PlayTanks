// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "TanksCameraActor.generated.h"

UCLASS()
class PLAYTANKS_API ATanksCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	ATanksCameraActor();
	virtual void BeginPlay() override;
};

UCLASS()
class PLAYTANKS_API ATanksChaseCam : public ATanksCameraActor
{
	GENERATED_BODY()

public:
	ATanksChaseCam();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bShowDebugInfo : 1;

	// The ideal distance that this camera will maintain from the follow target (Instigator).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector IdealOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CameraSpeed_PerAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraSpeedLimiter;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FRotator IdealRotOffset;
};