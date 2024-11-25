// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "CharacterPool.h"

ATestCharacter::ATestCharacter()
{
}

void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	if (world)
	{
		ACharacterPool* characterPool = ACharacterPool::GetInstance();
		characterPool->CreatePool(world);
 		characterPool->CharacterInsert(characterPool->CharacterAcquire(1));
	}

}

void ATestCharacter::CharacterMove()
{
	Super::CharacterMove();

}

void ATestCharacter::CharacterAction()
{
	Super::CharacterAction();
	UE_LOG(LogTemp, Log, TEXT("HI"));
}

void ATestCharacter::CharacterMouseMove()
{
	Super::CharacterMouseMove();
}
