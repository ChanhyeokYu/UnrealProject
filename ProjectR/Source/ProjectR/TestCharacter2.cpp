// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter2.h"
#include "CharacterPool.h"
#include "MainPlayerController.h"


ATestCharacter2::ATestCharacter2()
{
	
}

void ATestCharacter2::BeginPlay()
{
	Super::BeginPlay();
	SetOwnNum(2);
	ACharacterPool* characterPool = ACharacterPool::GetInstance();
	characterPool->CharacterInsert(this, GetOwnNum());
}

void ATestCharacter2::CharacterMove()
{
}

void ATestCharacter2::CharacterAction()
{
}

void ATestCharacter2::CharacterMouseMove()
{
}

void ATestCharacter2::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);
	/*if (controller)
	{
		AMainPlayerController* MPC = Cast<AMainPlayerController>(controller);

		EnableInput(MPC);
		MPC->SetViewTargetWithBlend(this, 0.5f);
	}*/


}
