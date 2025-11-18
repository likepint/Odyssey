#include "Components/CWeaponComponentAsset.h"
#include "Global.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Components/CWeaponComponent.h"

UCWeaponComponentAsset::UCWeaponComponentAsset()
{
	// Sword
	CHelpers::GetAsset<UInputAction>(InputActions[(int32)EWeaponInputAction::Sword], TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Sword.IA_Sword'"));

	// Attack
	CHelpers::GetAsset<UInputAction>(InputActions[(int32)EWeaponInputAction::Attack],TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Attack.IA_Attack'"));
}

void UCWeaponComponentAsset::BindInput(UCWeaponComponent* InWeaponComponent, UEnhancedInputComponent* InEnhancedInputComponent)
{
	if (InputActions[(int32)EWeaponInputAction::Sword])
		InEnhancedInputComponent->BindAction(InputActions[(int32)EWeaponInputAction::Sword], ETriggerEvent::Started, InWeaponComponent, &UCWeaponComponent::OnSwordMode);

	if (InputActions[(int32)EWeaponInputAction::Attack])
		InEnhancedInputComponent->BindAction(InputActions[(int32)EWeaponInputAction::Attack], ETriggerEvent::Started, InWeaponComponent, &UCWeaponComponent::OnAttack);
}
