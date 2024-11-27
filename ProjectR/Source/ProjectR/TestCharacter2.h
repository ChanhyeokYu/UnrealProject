// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "TestCharacter2.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ATestCharacter2 : public AMainCharacter
{
	GENERATED_BODY()

public:
	ATestCharacter2();

protected:
	void BeginPlay() override;

public:
	virtual void CharacterMove() override;
	virtual void CharacterAction() override;
	virtual	void CharacterMouseMove() override;

public:
	virtual int32 GetOwnNum() override { return _ownNum; }
	virtual void SetOwnNum(int32 ownNum) override { _ownNum = ownNum; }

	void PossessedBy(AController* controller) override;

private:
	int32 _ownNum = 0;
	
};
