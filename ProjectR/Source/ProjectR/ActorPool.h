// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPool.generated.h"

class AMainCharacter;

UCLASS()
class PROJECTR_API AActorPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	TSubclassOf<AActor> _pooledActorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int32 _poolSize;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	AActor* AcquireActor();
	void ReleaseActor(AActor* actorToRelease);

private:
	TArray<AActor*> _freePool;

};
