#include "Components/CMovementComponentAsset.h"
#include "Global.h"
#include "InputAction.h"
#include "Characters/CCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/CMovementComponent.h"

void FDodgeData::PlayDodgeMontage(ACCharacter* InOwnerCharacter)
{
	if (DodgeMontage)
		InOwnerCharacter->PlayAnimMontage(DodgeMontage, PlayRate);
}

UCMovementComponentAsset::UCMovementComponentAsset()
{
	// Movement
	CHelpers::GetAsset<UInputAction>(InputActions[(int32)EMovementInputAction::Movement], TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Movement.IA_Movement'"));

	// Crouch
	CHelpers::GetAsset<UInputAction>(InputActions[(int32)EMovementInputAction::Crouch], TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Crouch.IA_Crouch'"));

	// Sprint
	CHelpers::GetAsset<UInputAction>(InputActions[(int32)EMovementInputAction::Sprint], TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Sprint.IA_Sprint'"));

	// Walk
	CHelpers::GetAsset<UInputAction>(InputActions[(int32)EMovementInputAction::Walk], TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Walk.IA_Walk'"));

	// Look
	CHelpers::GetAsset<UInputAction>(InputActions[(int32)EMovementInputAction::Look],TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Look.IA_Look'"));

	// Dodge
	CHelpers::GetAsset<UInputAction>(InputActions[(int32)EMovementInputAction::Dodge],TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Dodge.IA_Dodge'"));

	// DodgeMontage
	CHelpers::GetAsset<UAnimMontage>(DodgeData.DodgeMontage, TEXT("/Script/Engine.AnimMontage'/Game/Characters/Misthios/Animations/Dodge/Dodge_Montage.Dodge_Montage'"));
}

void UCMovementComponentAsset::BindInput(UCMovementComponent* InMovementComponent, UEnhancedInputComponent* InEnhancedInputComponent)
{
	if (InputActions[(int32)EMovementInputAction::Movement])
	{
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Movement], ETriggerEvent::Triggered, InMovementComponent, &UCMovementComponent::OnMovement);
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Movement], ETriggerEvent::Completed, InMovementComponent, &UCMovementComponent::OffMovement);
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Movement], ETriggerEvent::Canceled, InMovementComponent, &UCMovementComponent::OffMovement);
	}

	if (InputActions[(int32)EMovementInputAction::Crouch])
	{
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Crouch], ETriggerEvent::Started, InMovementComponent, &UCMovementComponent::OnCrouch);
	}

	if (InputActions[(int32)EMovementInputAction::Sprint])
	{
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Sprint], ETriggerEvent::Started, InMovementComponent, &UCMovementComponent::OnSprint);
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Sprint], ETriggerEvent::Canceled, InMovementComponent, &UCMovementComponent::OnSprint);
	}

	if (InputActions[(int32)EMovementInputAction::Walk])
	{
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Walk], ETriggerEvent::Triggered, InMovementComponent, &UCMovementComponent::OnWalk);
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Walk], ETriggerEvent::Completed, InMovementComponent, &UCMovementComponent::OffWalk);
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Walk], ETriggerEvent::Canceled, InMovementComponent, &UCMovementComponent::OffWalk);
	}

	if (InputActions[(int32)EMovementInputAction::Look])
	{
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Look], ETriggerEvent::Triggered, InMovementComponent, &UCMovementComponent::OnLook);
	}

	if (InputActions[(int32)EMovementInputAction::Dodge])
	{
		InEnhancedInputComponent->BindAction(InputActions[(int32)EMovementInputAction::Dodge], ETriggerEvent::Started, InMovementComponent, &UCMovementComponent::OnDodge);
	}
}
