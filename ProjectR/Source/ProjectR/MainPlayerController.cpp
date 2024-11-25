// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MainCharacter.h"
#include "CharacterPool.h"


AMainPlayerController::AMainPlayerController()
{
	
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MappingContext();
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	BindingInput();
}

void AMainPlayerController::MappingContext()
{
	if (!_inputMappingContext.IsValid())
	{
		_inputMappingContext.LoadSynchronous();

	}

	ULocalPlayer* localPlayer = GetLocalPlayer();
	if (localPlayer)
	{
		UEnhancedInputLocalPlayerSubsystem* subsytem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(localPlayer);
		if (subsytem)
		{
			LoadedMappingContext = _inputMappingContext.Get();
			{
				subsytem->AddMappingContext(LoadedMappingContext, 0);
			}
		}
	}
}

void AMainPlayerController::BindingInput()
{
	if (!_playerMove.IsValid())
	{
		_playerMove.LoadSynchronous();
	}
	if (!_playerAction.IsValid())
	{
		_playerAction.LoadSynchronous();
	}
	if (!_playerMouseMove.IsValid())
	{
		_playerMouseMove.LoadSynchronous();
	}
	if (!_PlayerUtils.IsValid())
	{
		_PlayerUtils.LoadSynchronous();
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (_playerMove)
		{
			EnhancedInputComponent->BindAction(_playerMove.Get(), ETriggerEvent::Triggered, this, &ThisClass::PlayerMove);
		}
		if (_playerAction)
		{
			EnhancedInputComponent->BindAction(_playerAction.Get(), ETriggerEvent::Triggered, this, &ThisClass::PlayerAction);
		}
		if (_playerMouseMove)
		{
			EnhancedInputComponent->BindAction(_playerMouseMove.Get(), ETriggerEvent::Triggered, this, &ThisClass::PlayerMouseMove);
		}
		if (_PlayerUtils)
		{
			EnhancedInputComponent->BindAction(_PlayerUtils.Get(), ETriggerEvent::Triggered, this, &ThisClass::PlayerMouseMove);

		}
	}
}

void AMainPlayerController::PlayerMove(const FInputActionValue& value)
{
	APawn* pawn = GetPawn();
	FVector2D movementVector2D = value.Get<FVector2D>();

	const FRotator Rotation = K2_GetActorRotation();
	const FRotator yawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetScaledAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(yawRotation).GetScaledAxis(EAxis::Y);
	pawn->AddMovementInput(forwardDirection, movementVector2D.X);
	pawn->AddMovementInput(RightDirection, movementVector2D.Y);


}

void AMainPlayerController::PlayerAction(const FInputActionValue& value)
{
	AMainCharacter* mainCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	mainCharacter->CharacterAction();
}

void AMainPlayerController::PlayerMouseMove(const FInputActionValue& value)
{
	APawn* pawn = GetPawn();
	FVector2D lookAxisVector = value.Get<FVector2D>();

	pawn->AddControllerYawInput(lookAxisVector.X);
	pawn->AddControllerPitchInput(lookAxisVector.Y);
}

void AMainPlayerController::PlayerUtils(const FInputActionValue& value)
{
	/*switch (value.Get<int32>())
	{
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}*/
}
