#include "Items/Equipments/Weapons/CWeapon_EquipManager.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"

void UCWeapon_EquipManager::BeginPlay(ACCharacter* InOwner, const FEquipData& InEquipData, const FUnequipData& InUnequipData)
{
	OwnerCharacter = InOwner;
	EquipData = InEquipData;
	UnequipData = InUnequipData;

	StateComponent = OwnerCharacter->GetComponentByClass<UCStateComponent>();
	MovementComponent = OwnerCharacter->GetComponentByClass<UCMovementComponent>();
}

void UCWeapon_EquipManager::Equip_Implementation()
{
	CheckNull(OwnerCharacter);

	if (StateComponent)
		StateComponent->SetEquippingState();

	if (MovementComponent)
	{
		MovementComponent->SetMovable(EquipData.bMovable);
		MovementComponent->SetControlRotation(EquipData.bUseControlRotation);
	}

	if (EquipData.EquipMontage and !StateComponent->IsAttackingState())
	{
		OwnerCharacter->PlayAnimMontage(EquipData.EquipMontage, EquipData.PlayRate);

		return;
	}

	Begin_Equip();
	End_Equip();
}

void UCWeapon_EquipManager::Begin_Equip_Implementation()
{
	CheckNull(OwnerCharacter);

	bBeginEquip = true;

	if (OnEquipmentBeginEquip.IsBound())
		OnEquipmentBeginEquip.Broadcast();
}

void UCWeapon_EquipManager::End_Equip_Implementation()
{
	CheckNull(OwnerCharacter);

	bBeginEquip = false;
	bEquipped = true;

	if (StateComponent)
		StateComponent->SetIdleState();

	if (MovementComponent)
		MovementComponent->SetMovable(true);
}

void UCWeapon_EquipManager::Unequip_Implementation()
{
	CheckNull(OwnerCharacter);

	if (MovementComponent)
	{
		MovementComponent->SetMovable(UnequipData.bMovable);
		MovementComponent->SetControlRotation(UnequipData.bUseControlRotation);
	}

	if (UnequipData.UnequipMontage and !StateComponent->IsAttackingState())
	{
		OwnerCharacter->PlayAnimMontage(UnequipData.UnequipMontage, UnequipData.PlayRate);

		return;
	}

	End_Unequip();
}

void UCWeapon_EquipManager::End_Unequip_Implementation()
{
	bEquipped = false;

	if (OnEquipmentBeginUnequip.IsBound())
		OnEquipmentBeginUnequip.Broadcast();
}
