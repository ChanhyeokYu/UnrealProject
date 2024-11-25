// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

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
	void PlayerUtils(const FInputActionValue& value);

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

};
