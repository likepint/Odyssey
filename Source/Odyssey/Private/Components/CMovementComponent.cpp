#include "Components/CMovementComponent.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/CMovementComponent_DataAsset.h"
#include "Components/CCharacterMovementComponent.h"
#include "Components/CStateComponent.h"

UCMovementComponent::UCMovementComponent()
{
	MovementComponentAsset = FSoftObjectPath(TEXT("/Script/Odyssey.CMovement_DataAsset'/Game/Components/DA_Movement.DA_Movement'"));
	
	PrimaryComponentTick.bCanEverTick = true;
}

void UCMovementComponent::BindInput(UEnhancedInputComponent* InEnhancedInputComponent)
{
	CheckNull(InEnhancedInputComponent);

	if (UInputAction* movement = CHelpers::LoadSynchronous(MovementComponentAsset->IA_Movement))
	{
		InEnhancedInputComponent->BindAction(movement, ETriggerEvent::Triggered, this, &UCMovementComponent::OnMovement);
		InEnhancedInputComponent->BindAction(movement, ETriggerEvent::Completed, this, &UCMovementComponent::OffMovement);
		InEnhancedInputComponent->BindAction(movement, ETriggerEvent::Canceled, this, &UCMovementComponent::OffMovement);
	}

	if (UInputAction* crouch = CHelpers::LoadSynchronous(MovementComponentAsset->IA_Crouch))
	{
		InEnhancedInputComponent->BindAction(crouch, ETriggerEvent::Started, this, &UCMovementComponent::OnCrouch);
	}

	if (UInputAction* sprint = CHelpers::LoadSynchronous(MovementComponentAsset->IA_Sprint))
	{
		InEnhancedInputComponent->BindAction(sprint, ETriggerEvent::Started, this, &UCMovementComponent::OnSprint);
		InEnhancedInputComponent->BindAction(sprint, ETriggerEvent::Canceled, this, &UCMovementComponent::OnSprint);
	}

	if (UInputAction* walk = CHelpers::LoadSynchronous(MovementComponentAsset->IA_Walk))
	{
		InEnhancedInputComponent->BindAction(walk, ETriggerEvent::Triggered, this, &UCMovementComponent::OnWalk);
		InEnhancedInputComponent->BindAction(walk, ETriggerEvent::Completed, this, &UCMovementComponent::OffWalk);
		InEnhancedInputComponent->BindAction(walk, ETriggerEvent::Canceled, this, &UCMovementComponent::OffWalk);
	}

	if (UInputAction* look = CHelpers::LoadSynchronous(MovementComponentAsset->IA_Look))
	{
		InEnhancedInputComponent->BindAction(look, ETriggerEvent::Triggered, this, &UCMovementComponent::OnLook);
	}

	if (UInputAction* dodge = CHelpers::LoadSynchronous(MovementComponentAsset->IA_Dodge))
	{
		InEnhancedInputComponent->BindAction(dodge, ETriggerEvent::Started, this, &UCMovementComponent::OnDodge);
	}
}

void UCMovementComponent::SetTargetSpeed(ESpeedType InType)
{
	TargetSpeed = Speed[(int32)InType];
}

void UCMovementComponent::SetMovable(bool bInMovable)
{
	bMovable = bInMovable;
}

void UCMovementComponent::SetRotatable(bool bInRotatable)
{
	bRotatable = bInRotatable;
}

void UCMovementComponent::SetControlRotation(bool bInControlRotation)
{
	OwnerCharacter->bUseControllerRotationYaw = bInControlRotation;
	OwnerCharacter->GetComponentByClass<UCCharacterMovementComponent>()->bOrientRotationToMovement = !bInControlRotation;
}

void UCMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MovementComponentAsset)
		MovementComponentAsset->BeginPlay();
}

void UCMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetMaxWalkSpeed(DeltaTime);
}

void UCMovementComponent::SetMaxWalkSpeed(const float& InDeltaTime)
{
	if (bCrouched)
	{
		if (bWantsToWalk)
		{
			SetTargetSpeed(ESpeedType::CrouchedWalk);
		}
		else if (bWantsToRun)
		{
			SetTargetSpeed(ESpeedType::CrouchedRun);
		}
		else
		{
			SetTargetSpeed(ESpeedType::Idle);
		}
	}
	else
	{
		if (bWantsToWalk)
		{
			SetTargetSpeed(ESpeedType::StandingWalk);
		}
		else if (bWantsToRun)
		{
			SetTargetSpeed(ESpeedType::StandingRun);

			if (bWantsToSprint)
				SetTargetSpeed(ESpeedType::StandingSprint);
		}
		else
		{
			SetTargetSpeed(ESpeedType::Idle);
		}
	}

	UCCharacterMovementComponent* movement = OwnerCharacter->GetComponentByClass<UCCharacterMovementComponent>();
	movement->MaxWalkSpeed = FMath::FInterpTo(movement->MaxWalkSpeed, TargetSpeed, InDeltaTime, TargetSpeedInterpRate);
}

void UCMovementComponent::OnMovement(const FInputActionValue& InValue)
{
	CheckNull(OwnerCharacter);
	CheckFalse(bMovable);

	bWantsToRun = true;

	const FRotator yawRotator = FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0);

	const FVector2D value = InValue.Get<FVector2D>();

	const FVector forward = FQuat(yawRotator).GetForwardVector() * value.X;
	const FVector rightward = FQuat(yawRotator).GetRightVector() * value.Y;

	const FVector direction = forward + rightward;

	OwnerCharacter->AddMovementInput(direction.GetSafeNormal());
}

void UCMovementComponent::OffMovement(const FInputActionValue& InValue)
{
	CheckNull(OwnerCharacter);

	bWantsToRun = false;
	bWantsToWalk = false;
	bWantsToSprint = false;
}

void UCMovementComponent::OnCrouch(const FInputActionValue& InValue)
{
	CheckNull(OwnerCharacter);
	CheckFalse(bMovable);

	bWantsToWalk = false;
	bWantsToSprint = false;

	bCrouched = !bCrouched;

	bCrouched ? OwnerCharacter->Crouch() : OwnerCharacter->UnCrouch();
}

void UCMovementComponent::OnWalk(const FInputActionValue& InValue)
{
	CheckNull(OwnerCharacter);
	CheckFalse(bMovable);

	bWantsToWalk = true;
	bWantsToSprint = false;
}

void UCMovementComponent::OffWalk(const FInputActionValue& InValue)
{
	CheckNull(OwnerCharacter);
	CheckFalse(bMovable);

	bWantsToWalk = false;
}

void UCMovementComponent::OnSprint(const FInputActionValue& InValue)
{
	CheckNull(OwnerCharacter);
	CheckFalse(bMovable);
	CheckFalse(bWantsToRun);

	bWantsToSprint = !bWantsToSprint;
}

void UCMovementComponent::OnLook(const FInputActionValue& InValue)
{
	CheckNull(OwnerCharacter);
	CheckFalse(bRotatable);

	const FVector2D value = InValue.Get<FVector2D>();

	// 좌우
	OwnerCharacter->AddControllerYawInput(value.X * Sensitivity.X * GetWorld()->GetDeltaSeconds());

	// 수직
	OwnerCharacter->AddControllerPitchInput(value.Y * Sensitivity.Y * GetWorld()->GetDeltaSeconds());
}

void UCMovementComponent::OnDodge(const FInputActionValue& InValue)
{
	CheckNull(OwnerCharacter);
	CheckFalse(bMovable);

	bWantsToRun = false;
	bWantsToWalk = false;
	bWantsToSprint = false;

	if (UCStateComponent* state = OwnerCharacter->GetComponentByClass<UCStateComponent>())
	{
		CheckTrue(state->IsDodgeState());

		state->SetDodgeState();
	}

	MovementComponentAsset->DodgeData.PlayDodgeMontage(OwnerCharacter);
}
