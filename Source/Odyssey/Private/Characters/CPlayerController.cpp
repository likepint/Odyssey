#include "Characters/CPlayerController.h"
#include "Global.h"
#include "Characters/CMappingContextAsset.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"

ACPlayerController::ACPlayerController()
{
	// MappingContextAsset
	CHelpers::GetAsset<UCMappingContextAsset>(MappingContextAsset, TEXT("/Script/Odyssey.CMappingContextAsset'/Game/Characters/Misthios/DA_MappingContext.DA_MappingContext'"));

	PrimaryActorTick.bCanEverTick = true;
}

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsLocalPlayerController())
	{
		if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			subsystem->ClearAllMappings();

			if (MappingContextAsset)
				MappingContextAsset->OnPossess(subsystem);
		}

		if (TObjectPtr<UEnhancedInputComponent> enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			if (TObjectPtr<UCMovementComponent> movement = GetPawn()->GetComponentByClass<UCMovementComponent>())
				movement->BindInput(enhancedInputComponent);

			if (TObjectPtr<UCWeaponComponent> weapon = GetPawn()->GetComponentByClass<UCWeaponComponent>())
				weapon->BindInput(enhancedInputComponent);
		}
	}
}
