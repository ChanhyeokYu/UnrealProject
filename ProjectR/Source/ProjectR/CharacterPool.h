// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterPool.generated.h"

class AMainCharacter;
class AActorPool;

USTRUCT(BlueprintType)
struct FCharacterStruct
{
	GENERATED_BODY()

	int32 characterNum;
	AMainCharacter* swapCharacter;
	bool characterFront = false;
};

UCLASS()
class PROJECTR_API ACharacterPool : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterPool();
	static ACharacterPool* GetInstance()
	{
		if (!Instacne)
		{
			Instacne = NewObject<ACharacterPool>();
			Instacne->AddToRoot();
		}
		return Instacne;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void CreatePool(UWorld* world);

public:
	void CharacterInsert(AMainCharacter* mainCharacter);
	AMainCharacter* CharacterAcquire(int32 characterNum);
private:
private:
	TArray<FCharacterStruct> _characterPool = {};
	int32 _characterPoolSize = 4;
	AActorPool* _actorPool;
	
	static ACharacterPool* Instacne;
};
ACharacterPool* ACharacterPool::Instacne = nullptr;