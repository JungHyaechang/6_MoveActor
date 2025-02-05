// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComponent);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneComponent);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMeshComp->SetCollisionResponseToAllChannels(ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/Floor_400x400.Floor_400x400"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Wood_Oak.M_Wood_Oak"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	MaxDistance = 300.0f;
	MoveSpeed = 100.0f;

	CurrentOffset = 0.0f;
	Direction = 1;
}


void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FMath::Abs(CurrentOffset) >= MaxDistance)
	{
		Direction *= -1;
	}

	float MoveStep = MoveSpeed * DeltaTime * Direction;
	CurrentOffset += MoveStep;
	
	AddActorLocalOffset(FVector(MoveStep, 0.0f, 0.0f), true); // Sweep È°¼ºÈ­
}

