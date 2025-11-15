#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACCharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter)
	{
		Speed = OwnerCharacter->GetVelocity().Size2D();

		const FRotator velocityRot = OwnerCharacter->GetVelocity().ToOrientationRotator();
		const FRotator actorRot = OwnerCharacter->GetActorRotation();
		const FRotator deltaRot = UKismetMathLibrary::NormalizedDeltaRotator(velocityRot, actorRot);
		PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, deltaRot, DeltaSeconds, RotationInterpSpeed);
		Direction = PrevRotation.Yaw;

		bMovable = (Speed > 0.0f and !OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Equals(FVector::Zero()));

		if (UCMovementComponent* movement = OwnerCharacter->GetComponentByClass<UCMovementComponent>())
			bCrouched = movement->IsCrouched();
	}
}
