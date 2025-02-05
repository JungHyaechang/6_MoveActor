// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"
#include "Spawner.h"
#include "EngineUtils.h" // TActorIterator ����� ���� �ʿ�
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

	AngularSpeed = 180.0f; // 1�ʿ� 180�� degree ��(����)
}

void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	RandomAngleDegree = FMath::FRandRange(0.0f, 80.0f);
	ASpawner* Spawner = nullptr;
	if (GetWorld())
	{
		for (TActorIterator<ASpawner> It(GetWorld()); It; ++It) // ASpawner Ÿ�� ���� �˻�; ��ȿ���� �Ǵ�; ���������� Ž�� (���Ϳ� ���� ������ ��� ���)
		{
			Spawner = *It;
			break; // ù ��°�� ã�� ���͸� ���
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

	// ���� �̵� 
	float DeltaAngle = FMath::DegreesToRadians(AngularSpeed * DeltaTime);
	CurrentRidian += DeltaAngle;
	
	float NewX = CenterLocation.X + (Radius * FMath::Cos(CurrentRidian));
	float NewY = CenterLocation.Y + (Radius * FMath::Sin(CurrentRidian));
	float NewZ = GetActorLocation().Z;

	FVector NewLocation(NewX, NewY, NewZ);

	// ���� ȸ�� 
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation += FRotator(0.0f, RandomAngleDegree * DeltaTime, RandomAngleDegree * DeltaTime);

	SetActorLocation(NewLocation);
	SetActorRotation(CurrentRotation);
}

