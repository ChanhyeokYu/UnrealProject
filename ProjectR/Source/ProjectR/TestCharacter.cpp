// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "CharacterPool.h"

ATestCharacter::ATestCharacter()
{
}

void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetOwnNum(1);
	ACharacterPool* characterPool = ACharacterPool::GetInstance();
	characterPool->CharacterInsert(this, GetOwnNum());
}

void ATestCharacter::CharacterMove()
{
	Super::CharacterMove();

}

void ATestCharacter::CharacterAction()
{
	Super::CharacterAction();
}

void ATestCharacter::CharacterMouseMove()
{
	Super::CharacterMouseMove();
}
