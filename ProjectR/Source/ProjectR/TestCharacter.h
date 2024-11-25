// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "TestCharacter.generated.h"

UCLASS()
class PROJECTR_API ATestCharacter : public AMainCharacter
{
	GENERATED_BODY()

public:
	ATestCharacter();
	
protected:
	void BeginPlay() override;

public:
	virtual void CharacterMove() override;
	virtual void CharacterAction() override;
	virtual	void CharacterMouseMove() override;
	
};
