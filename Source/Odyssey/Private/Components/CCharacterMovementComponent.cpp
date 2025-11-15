#include "Components/CCharacterMovementComponent.h"

UCCharacterMovementComponent::UCCharacterMovementComponent()
{
	CrouchedHalfHeight = 65.0f;
	
	MaxWalkSpeed = 0.0f;
	
	RotationRate = FRotator(0, 360, 0);
	bOrientRotationToMovement = true;
	
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}
