// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

// Sets default values
AActorPool::AActorPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_poolSize = 4;
}

// Called when the game starts or when spawned
void AActorPool::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < _poolSize; i++)
	{
		AActor* newActor = GetWorld()->SpawnActor<AActor>(_pooledActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (newActor)
		{
			newActor->SetActorEnableCollision(false);
			newActor->SetActorHiddenInGame(true);
			newActor->SetActorTickEnabled(false);
			_freePool.Add(newActor);
		}
	}

}

// Called every frame
void AActorPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* AActorPool::AcquireActor()
{
	for (AActor* Actor : _freePool )
	{
		if (!Actor->IsActorTickEnabled())
		{
			Actor->SetActorEnableCollision(true);
			Actor->SetActorHiddenInGame(false);
			Actor->SetActorTickEnabled(true);
			return Actor;
		}
	}
	return nullptr;
}

void AActorPool::ReleaseActor(AActor* actorToRelease)
{
	if (actorToRelease)
	{
		actorToRelease->SetActorEnableCollision(false);
		actorToRelease->SetActorHiddenInGame(true);
		actorToRelease->SetActorTickEnabled(false);
	}
}

