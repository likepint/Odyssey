#include "Components/CMovementComponent_DataAsset.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CMovementComponent.h"

FDodgeData::FDodgeData()
{
	// DodgeMontagePath
	DodgeMontagePath = FSoftObjectPath(TEXT("/Script/Engine.AnimMontage'/Game/Characters/Misthios/Animations/Dodge/Dodge_Montage.Dodge_Montage'"));
}

void FDodgeData::BeginPlay()
{
	if (UAnimMontage* montage = CHelpers::LoadSynchronous(DodgeMontagePath))
		DodgeMontage = montage;
}

void FDodgeData::PlayDodgeMontage(ACCharacter* InOwnerCharacter)
{
	if (DodgeMontage)
		InOwnerCharacter->PlayAnimMontage(DodgeMontage, PlayRate);
}

UCMovementComponent_DataAsset::UCMovementComponent_DataAsset()
{
	// Movement
	IA_Movement = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Movement.IA_Movement'"));

	// Crouch
	IA_Crouch = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Crouch.IA_Crouch'"));

	// Sprint
	IA_Sprint = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Sprint.IA_Sprint'"));

	// Walk
	IA_Walk = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Walk.IA_Walk'"));

	// Look
	IA_Look = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Look.IA_Look'"));

	// Dodge
	IA_Dodge = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Dodge.IA_Dodge'"));
}

void UCMovementComponent_DataAsset::BeginPlay()
{
	DodgeData.BeginPlay();
}
