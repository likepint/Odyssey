#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "Components/CWeaponComponentAsset.h"
#include "Characters/CCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/CStateComponent.h"
#include "Items/Equipments/Weapons/CWeapon_DataAsset.h"
#include "Items/Equipments/Weapons/CWeapon_Data.h"
#include "Items/Equipments/Weapons/CWeapon_Attachment.h"
#include "Items/Equipments/Weapons/CWeapon_AttackManager.h"
#include "Items/Equipments/Weapons/CWeapon_EquipManager.h"

UCWeaponComponent::UCWeaponComponent()
{
	// WeaponComponentAsset
	CHelpers::GetAsset<UCWeaponComponentAsset>(WeaponComponentAsset, TEXT("/Script/Odyssey.CWeaponComponentAsset'/Game/Components/DA_WeaponComponent.DA_WeaponComponent'"));

	PrimaryComponentTick.bCanEverTick = true;
}

void UCWeaponComponent::BindInput(UEnhancedInputComponent* InEnhancedInputComponent)
{
	CheckNull(InEnhancedInputComponent);

	if (WeaponComponentAsset)
		WeaponComponentAsset->BindInput(this, InEnhancedInputComponent);
}

TObjectPtr<ACWeapon_Attachment> UCWeaponComponent::GetAttachment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(WeaponDatas[(int32)WeaponType], nullptr);

	return WeaponDatas[(int32)WeaponType]->GetAttachment();
}

TObjectPtr<UCWeapon_EquipManager> UCWeaponComponent::GetEquipManager()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(WeaponDatas[(int32)WeaponType], nullptr);

	return WeaponDatas[(int32)WeaponType]->GetEquipManager();
}

TObjectPtr<UCWeapon_AttackManager> UCWeaponComponent::GetAttackManager()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(WeaponDatas[(int32)WeaponType], nullptr);

	return WeaponDatas[(int32)WeaponType]->GetAttackManager();
}

void UCWeaponComponent::End_Unequip()
{
	ChangeType(EWeaponType::Max);
}

void UCWeaponComponent::OnUnarmedMode()
{
	GetEquipManager()->Unequip();
}

void UCWeaponComponent::OnSwordMode()
{
	CheckFalse(IsIdleState());

	SetWeaponType(EWeaponType::Sword);
}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int32 idx = 0; idx < (int32)EWeaponType::Max; ++idx)
	{
		if (WeaponAssets[idx])
			WeaponAssets[idx]->BeginPlay(OwnerCharacter, WeaponDatas[idx]);
	}
}

bool UCWeaponComponent::IsIdleState() const
{
	return OwnerCharacter->GetComponentByClass<UCStateComponent>()->IsIdleState();
}

bool UCWeaponComponent::IsAttackingState() const
{
	return OwnerCharacter->GetComponentByClass<UCStateComponent>()->IsAttackingState();
}

void UCWeaponComponent::SetWeaponType(EWeaponType InNewWeaponType)
{
	if (IsUnarmedMode())
	{
		if (IsAttackingState())
		{
			GetEquipManager()->ImmediatelyEquip();
		}
		else
		{
			if (WeaponDatas[(int32)InNewWeaponType])
				WeaponDatas[(int32)InNewWeaponType]->GetEquipManager()->Equip();

			ChangeType(InNewWeaponType);
		}

		return;
	}
	else // IsUnarmedMode == false
	{
		if (IsAttackingState())
		{
			GetEquipManager()->ImmediatelyUnequip();
			GetEquipManager()->ImmediatelyEquip();
			
			return;
		}

		if (WeaponDatas[(int32)InNewWeaponType])
		{
			WeaponDatas[(int32)InNewWeaponType]->GetEquipManager()->Equip();

			ChangeType(InNewWeaponType);
		}
	}
}

void UCWeaponComponent::ChangeType(EWeaponType InNewWeaponType)
{
	EWeaponType prevWeaponType = WeaponType;
	WeaponType = InNewWeaponType;

	if (OnWeaponTypeChange.IsBound())
		OnWeaponTypeChange.Broadcast(prevWeaponType, InNewWeaponType);
}

void UCWeaponComponent::OnAttack(const FInputActionValue& InValue)
{
	OnSwordMode();

	if (GetAttackManager())
		GetAttackManager()->Attack();
}
