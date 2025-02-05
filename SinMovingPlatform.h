// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SinMovingPlatform.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class ACTORPAWN_API ASinMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASinMovingPlatform();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RootComponent")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMeshComp")
	UStaticMeshComponent* StaticMeshComp;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotateSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector InitialPosition;

};
