// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPool.h"
#include "MainCharacter.h"
#include "ActorPool.h"
#include "Algo/Find.h"

// Sets default values
ACharacterPool::ACharacterPool()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterPool::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACharacterPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterPool::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterPool::CharacterInsert(AMainCharacter* mainCharacter)
{
	AMainCharacter* nowPlayer = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	mainCharacter = nowPlayer;
}

AMainCharacter* ACharacterPool::CharacterAcquire(int32 characterNum)
{

	int32 idx = _characterPool.IndexOfByPredicate([characterNum](const FCharacterStruct& element)
		{
			return element.characterNum == characterNum;
		});

	if (idx != INDEX_NONE && _characterPool[idx].characterFront)
	{
		return nullptr;
	}
	else
	{
		_characterPool[characterNum - 1].characterNum = characterNum;
	}

	for (FCharacterStruct poolStruct : _characterPool)
	{
		if (poolStruct.characterNum == characterNum)
		{
			if (poolStruct.characterFront)
			{
				poolStruct.characterFront = true;
				return poolStruct.swapCharacter;
			}
			else
			{
				return nullptr;
			}
		}
	}
	return nullptr;

}

void ACharacterPool::CreatePool(UWorld* world)
{
	for (int32 i = 0; i < _characterPoolSize; i++)
	{
		AMainCharacter* newCharacter = world->SpawnActor<AMainCharacter>(AMainCharacter::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		{
			newCharacter->SetActorTickEnabled(false);
			newCharacter->SetActorEnableCollision(false);
			newCharacter->SetActorHiddenInGame(true);
			int32 num = i;
			FCharacterStruct newCharacterStruce
			{
				i,
				newCharacter
			};
			_characterPool.Add(newCharacterStruce);
		}
	}
}

