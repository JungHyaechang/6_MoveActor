// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "SpawnActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ASpawner::ASpawner()
{

	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneComponent);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMeshComp->SetCollisionResponseToAllChannels(ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_TableRound.SM_TableRound"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Props/Materials/M_TableRound.M_TableRound"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnRandomActor, 8.0f, true, 3.0f);

}

void ASpawner::SpawnRandomActor()
{
	TSubclassOf<ASpawnActor> SpawnActor = ASpawnActor::StaticClass();

	int32 NumSpawnActor = FMath::RandRange(5, 10);

	for (int32 i = 0; i < NumSpawnActor; i++)
	{
		float RandomDistance = FMath::RandRange(500.0f, 1000.0f);
		float RandomAngleDegrees = FMath::RandRange(0.0f, 360.0f);
		float RandomAngleRadians = FMath::DegreesToRadians(RandomAngleDegrees);
		float RandomHeight = FMath::FRandRange(0.0f, 200.0f);

		// ·£´ý Offset
		FVector SpawnOffest = FVector(RandomDistance * FMath::Cos(RandomAngleRadians),	// X = ºøº¯(RandomDistance) * Cos(RandomAngleRadians) 
			RandomDistance * FMath::Sin(RandomAngleRadians),							// Y = ºøº¯ * Sin(RandomAngleRadians)				
			RandomHeight);

		FVector SpawnLocation = GetActorLocation() + SpawnOffest;

		ASpawnActor* SpawnedActor = GetWorld()->SpawnActor<ASpawnActor>(SpawnActor, SpawnLocation, { 0.f,0.f,0.f });

		if (SpawnedActor)
		{
			SpawnedActor->SetLifeSpan(5.0f); // »ý¼º ÈÄ, 5ÃÊµÚ ¼Ò¸ê
		}
	}
}