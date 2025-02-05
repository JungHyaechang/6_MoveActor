// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class ACTORPAWN_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RootComponent")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMeshComp")
	UStaticMeshComponent* StaticMeshComp;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Direction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CurrentOffset;
};
