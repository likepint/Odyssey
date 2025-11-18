#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// OwnerCharacter
	OwnerCharacter = Cast<ACCharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);

	// WeaponComponent
	WeaponComponent = OwnerCharacter->GetComponentByClass<UCWeaponComponent>();
	if (WeaponComponent)
		WeaponComponent->OnWeaponTypeChange.AddDynamic(this, &UCAnimInstance::OnWeaponTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter);

	// Speed
	Speed = OwnerCharacter->GetVelocity().Size2D();

	// Direction
	const FRotator velocityRot = OwnerCharacter->GetVelocity().ToOrientationRotator();
	const FRotator actorRot = OwnerCharacter->GetActorRotation();
	const FRotator deltaRot = UKismetMathLibrary::NormalizedDeltaRotator(velocityRot, actorRot);
	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, deltaRot, DeltaSeconds, RotationInterpSpeed);
	Direction = PrevRotation.Yaw;

	// bMovable
	bMovable = (Speed > 0.0f and !OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Equals(FVector::Zero()));

	// bCrouched
	if (UCMovementComponent* movement = OwnerCharacter->GetComponentByClass<UCMovementComponent>())
		bCrouched = movement->IsCrouched();
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InPrevWeaponType, EWeaponType InNewWeaponType)
{
	WeaponType = InNewWeaponType;
}
