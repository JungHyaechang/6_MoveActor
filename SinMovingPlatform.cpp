// Fill out your copyright notice in the Description page of Project Settings.


#include "SinMovingPlatform.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


ASinMovingPlatform::ASinMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
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
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Wood_Floor_Walnut_Worn.M_Wood_Floor_Walnut_Worn"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
	Amplitude = 300.0f;
	Frequency = 0.5f;
	RotateSpeed = 180.0f;
}

void ASinMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	InitialPosition = GetActorLocation();
}

void ASinMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Time = GetWorld()->GetTimeSeconds();
	float Offset = Amplitude * FMath::Sin(2 * PI * Frequency * Time);

	if (!FMath::IsNearlyZero(RotateSpeed)) {
		AddActorLocalRotation(FRotator(0.0f, RotateSpeed * DeltaTime, 0.0f));
	}
	SetActorLocation(InitialPosition + FVector(Offset, 0.0f, 0.0f));
}



