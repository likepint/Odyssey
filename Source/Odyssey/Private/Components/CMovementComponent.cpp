#include "Components/CMovementComponent.h"
#include "Global.h"
#include "Components/CMovementComponentAsset.h"
#include "Characters/CCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/CCharacterMovementComponent.h"
#include "Components/CStateComponent.h"

UCMovementComponent::UCMovementComponent()
{
	// MovementComponentAsset
	CHelpers::GetAsset<UCMovementComponentAsset>(MovementComponentAsset, TEXT("/Script/Odyssey.CMovementComponentAsset'/Game/Components/DA_MovementComponent.DA_MovementComponent'"));

	PrimaryComponentTick.bCanEverTick = true;
}

void UCMovementComponent::BindInput(UEnhancedInputComponent* InEnhancedInputComponent)
{
	CheckNull(InEnhancedInputComponent);

	if (MovementComponentAsset)
		MovementComponentAsset->BindInput(this, InEnhancedInputComponent);
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

	MovementComponentAsset->GetDodgeData().PlayDodgeMontage(OwnerCharacter);
}
