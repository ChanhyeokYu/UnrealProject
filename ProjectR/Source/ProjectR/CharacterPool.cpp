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

void ACharacterPool::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	GetInstance()->_world = GetWorld();
	GetInstance()->CreateCharacterPool();
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

void ACharacterPool::CharacterInsert(AMainCharacter* insertPlayer ,int32 characterNum)
{
	_characterPool[characterNum - 1].swapCharacter = insertPlayer;

	int32 idx = GetCharacterIndex(characterNum);
	if (!_characterPool[idx - 1].isCharacter)
	{
		_characterPool[idx - 1].isCharacter = true;
	}

}

void ACharacterPool::CharacterRelease(int32 characterNum)
{
	AMainCharacter* mainCharacter = Cast<AMainCharacter>(_world->GetFirstPlayerController()->GetCharacter());
	check(mainCharacter);

	int32 mainCharacterIdx = mainCharacter->GetOwnNum();

	if (_characterPool[mainCharacterIdx -1].characterNum == characterNum)
	{
		return;
	}

	int32 idx = GetCharacterIndex(characterNum);
	if (idx == -1)
	{
		return;
	}
	_characterPool[idx - 1].characterFront = false;

}

void ACharacterPool::CharacterSwap(int32 swapCharacterNum)
{
	int32 idx = GetCharacterIndex(swapCharacterNum);
	if (idx == -1)
	{
		return;
	}

	if (_characterPool[idx - 1].isCharacter)
	{
		_characterPool[idx - 1].characterFront = true;
	}

}

void ACharacterPool::CreateCharacterPool()
{
	UWorld* world = GetWorld();
	for (int32 i = 0; i < _characterPoolSize; i++)
	{
		AMainCharacter* newCharacter = _world->SpawnActor<AMainCharacter>(AMainCharacter::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
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

int32 ACharacterPool::GetCharacterIndex(int32 characterNum)
{
	return 	_characterPool.IndexOfByPredicate([characterNum](const FCharacterStruct& element)
		{
			return element.characterNum == characterNum;
		});
}

