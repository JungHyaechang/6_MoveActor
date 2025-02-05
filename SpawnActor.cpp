// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"
#include "Spawner.h"
#include "EngineUtils.h" // TActorIterator 사용을 위해 필요
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ASpawnActor::ASpawnActor()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneComponent);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMeshComp->SetCollisionResponseToAllChannels(ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Props/Materials/M_Chair.M_Chair"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	AngularSpeed = 180.0f; // 1초에 180도 degree 값(각도)
}

void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	RandomAngleDegree = FMath::FRandRange(0.0f, 80.0f);
	ASpawner* Spawner = nullptr;
	if (GetWorld())
	{
		for (TActorIterator<ASpawner> It(GetWorld()); It; ++It) // ASpawner 타입 액터 검색; 유효한지 판단; 순차적으로 탐색 (액터에 대한 참조를 얻는 방법)
		{
			Spawner = *It;
			break; // 첫 번째로 찾은 액터를 사용
		}
	}

	if (Spawner)
	{
		CenterLocation = Spawner->GetActorLocation();
		FVector Offset = GetActorLocation() - CenterLocation;
		Radius = Offset.Size();

		CurrentRidian = FMath::Atan2(Offset.Y, Offset.X);
	}
}

void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 공전 이동 
	float DeltaAngle = FMath::DegreesToRadians(AngularSpeed * DeltaTime);
	CurrentRidian += DeltaAngle;
	
	float NewX = CenterLocation.X + (Radius * FMath::Cos(CurrentRidian));
	float NewY = CenterLocation.Y + (Radius * FMath::Sin(CurrentRidian));
	float NewZ = GetActorLocation().Z;

	FVector NewLocation(NewX, NewY, NewZ);

	// 랜덤 회전 
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation += FRotator(0.0f, RandomAngleDegree * DeltaTime, RandomAngleDegree * DeltaTime);

	SetActorLocation(NewLocation);
	SetActorRotation(CurrentRotation);
}

