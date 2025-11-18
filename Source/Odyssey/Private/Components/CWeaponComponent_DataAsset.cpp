#include "Components/CWeaponComponent_DataAsset.h"

UCWeaponComponent_DataAsset::UCWeaponComponent_DataAsset()
{
	// Sword
	IA_Sword = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Sword.IA_Sword'"));

	// Attack
	IA_Attack = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Attack.IA_Attack'"));
}
