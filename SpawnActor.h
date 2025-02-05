// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class ACTORPAWN_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawnActor();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RootComponent")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMeshComp")
	UStaticMeshComponent* StaticMeshComp;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RandomAngleDegree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector CenterLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AngularSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CurrentRidian;
};
