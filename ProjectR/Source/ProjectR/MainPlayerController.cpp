// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MainCharacter.h"
#include "CharacterPool.h"
#include "GameFramework/CharacterMovementComponent.h"


AMainPlayerController::AMainPlayerController()
{
	
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MappingContext();
	//ACharacterPool* characterpool = ACharacterPool::GetInstance();
	/*characterpool->CharacterRelease(num);
	UnPossess();
	characterpool->CharacterSwap(num);*/
	//OnPossess(characterpool->GetCharacterpool()[0].swapCharacter);
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
			//EnhancedInputComponent->BindAction(_PlayerUtils.Get(), ETriggerEvent::Triggered, this, &ThisClass::PlayerUtils);
			InputComponent->BindKey(EKeys::One,	 IE_Pressed, this, &ThisClass::PlayerKey);
			InputComponent->BindKey(EKeys::Two, IE_Pressed, this, &ThisClass::PlayerKey);

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

void AMainPlayerController::PlayerKey(FKey key)
{
	FString keyName = key.GetDisplayName().ToString();
	int32 num = FCString::Atoi(*keyName);
	EKeyType keyType = StaticCast<EKeyType>(num);

	//케이스 없애고 그냥 번호만 받아서 변경 고려
	switch (keyType)
	{
	case EKeyType::KeyType1:
	{
		ACharacterPool* characterpool = ACharacterPool::GetInstance();
		characterpool->CharacterRelease(num);
		OnUnPossess();
		characterpool->CharacterSwap(num);
		OnPossess(characterpool->GetCharacterpool()[num - 1].swapCharacter);
	}
		break;
	case EKeyType::KeyType2:
	{
		ACharacterPool* characterpool = ACharacterPool::GetInstance();
		characterpool->CharacterRelease(num);
		OnUnPossess();
		characterpool->CharacterSwap(num);
		OnPossess(characterpool->GetCharacterpool()[num - 1].swapCharacter);
		
	}
		break;
	default:
		break;
	}

}

void AMainPlayerController::OnPossess(APawn* pawn)
{
	/*AController* oldcontroller = pawn->GetController();
	if (oldcontroller)
	{
		oldcontroller->UnPossess();
		oldcontroller->Destroy();
	}*/
	Super::OnPossess(pawn);
	check(pawn);
	if (pawn)
	{

		/*SetViewTargetWithBlend(pawn, 0.5f, VTBlend_Linear);
		pawn->bUseControllerRotationYaw = true;
		if (UCharacterMovementComponent* moveComp = Cast<UCharacterMovementComponent>(pawn->GetMovementComponent()))
		{
			moveComp->bOrientRotationToMovement = false;
		}*/
		//pawn->EnableInput(this);
		//FHitResult* HitResult;
		pawn->SetActorEnableCollision(true);
		pawn->SetActorHiddenInGame(false);
		pawn->SetActorTickEnabled(true);
		pawn->SetActorLocation(_actorLocation, false, nullptr, ETeleportType::TeleportPhysics);

		/*pawn->AutoPossessPlayer = EAutoReceiveInput::Player0;
		AttachToPawn(pawn);
		AddPawnTickDependency(pawn);*/
		
	}
}

void AMainPlayerController::OnUnPossess()
{
	APawn* pawn = GetPawn();
	check(pawn);
	if (pawn)
	{
		_actorLocation = pawn->GetActorLocation();
		pawn->SetActorEnableCollision(false);
		pawn->SetActorHiddenInGame(true);
		pawn->SetActorTickEnabled(false);
	}

	Super::OnUnPossess();
}
