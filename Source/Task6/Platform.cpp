// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform.h"

// Sets default values
APlatform::APlatform()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);


	// Script / Engine.StaticMesh'/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform'
	// Script / Engine.Material'/Game/Resources/Materials/M_Brick_Clay_Beveled.M_Brick_Clay_Beveled'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Brick_Clay_Beveled.M_Brick_Clay_Beveled"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 0.0f;
	MoveSpeed = 200.0f;
	MaxRange = 1000.0f;

}

// Called when the game starts or when spawned
void APlatform::BeginPlay()
{
	Super::BeginPlay();

	//SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	SetActorScale3D(FVector(1.0f));
	
	StartLocation = GetActorLocation();
}

// Called every frame
void APlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Time = GetGameTimeSinceCreation();
	float Offset = FMath::Sin(Time * MoveSpeed / MaxRange) * MaxRange;
	FVector NewLocation = StartLocation;
	NewLocation.Y += Offset;
	SetActorLocation(NewLocation);
}

void APlatform::ResetActorPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float APlatform::GetRotationSpeed() const
{
	return RotationSpeed;
}
