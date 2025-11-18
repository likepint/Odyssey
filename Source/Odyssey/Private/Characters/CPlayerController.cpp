#include "Characters/CPlayerController.h"
#include "Global.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"

ACPlayerController::ACPlayerController()
{
	// Locomotion
	IMC_Locomotion = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Locomotion.IMC_Locomotion'"));

	// Combat
	IMC_Combat = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Combat.IMC_Combat'"));

	PrimaryActorTick.bCanEverTick = true;
}

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			subsystem->ClearAllMappings();

			if (!IMC_Locomotion.IsNull())
			{
				if (UInputMappingContext* locomotion = IMC_Locomotion.LoadSynchronous())
					subsystem->AddMappingContext(locomotion, 0);
			}

			if (!IMC_Combat.IsNull())
			{
				if (UInputMappingContext* combat = IMC_Combat.LoadSynchronous())
					subsystem->AddMappingContext(combat, 1);
			}
		}

		if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			if (UCMovementComponent* movement = GetPawn()->GetComponentByClass<UCMovementComponent>())
				movement->BindInput(enhancedInputComponent);

			if (UCWeaponComponent* weapon = GetPawn()->GetComponentByClass<UCWeaponComponent>())
				weapon->BindInput(enhancedInputComponent);
		}
	}
}
