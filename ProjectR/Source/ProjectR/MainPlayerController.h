// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

UENUM(BlueprintType)
enum class EKeyType : uint8
{
	KeyType0 = 0 UMETA(DisplayName = "Key Type 0"),
	KeyType1 = 1 UMETA(DisplayName = "Key Type 1"),
	KeyType2 = 2 UMETA(DisplayName = "Key Type 2"),

};
/**
 * 
 */
UCLASS()
class PROJECTR_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();


public:
	void BeginPlay() override;
	void SetupInputComponent() override;

	void MappingContext();
	void BindingInput();

	void PlayerMove(const FInputActionValue& value);
	void PlayerAction(const FInputActionValue& value);
	void PlayerMouseMove(const FInputActionValue& value);
	void PlayerKey(FKey key);


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mapping")
	TSoftObjectPtr<UInputMappingContext> _inputMappingContext = nullptr;
	UInputMappingContext* LoadedMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputAction> _playerMove = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputAction> _playerAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputAction> _playerMouseMove = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputAction> _PlayerUtils= nullptr;

public:

	void OnPossess(APawn* pawn) override;
	void OnUnPossess() override;

private:
	FVector _actorLocation = { 0,0,0 };
};
