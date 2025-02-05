// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class ACTORPAWN_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawner();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RootComponent")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMeshComp")
	UStaticMeshComponent* StaticMeshComp;

	UFUNCTION()
	void SpawnRandomActor();

protected:

	virtual void BeginPlay() override;

	FTimerHandle SpawnTimerHandle;
};
