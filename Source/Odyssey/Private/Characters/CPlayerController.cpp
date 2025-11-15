#include "Characters/CPlayerController.h"
#include "Global.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CMovementComponent.h"

ACPlayerController::ACPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			CheckNull(IMC_Locomotion);
			subsystem->AddMappingContext(IMC_Locomotion, 0);
		}

		if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			if (UCMovementComponent* movement = Cast<UCMovementComponent>(GetPawn()->GetComponentByClass<UCMovementComponent>()))
				movement->BindInput(enhancedInputComponent);
		}
	}
}
