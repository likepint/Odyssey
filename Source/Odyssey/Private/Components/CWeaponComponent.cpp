#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "Components/CWeaponComponent_DataAsset.h"
#include "Characters/CCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/CStateComponent.h"
#include "Items/Equipments/Weapons/CWeapon_DataAsset.h"
#include "Items/Equipments/Weapons/CWeapon_Data.h"
#include "Items/Equipments/Weapons/CWeapon_Attachment.h"
#include "Items/Equipments/Weapons/CWeapon_EquipManager.h"

UCWeaponComponent::UCWeaponComponent()
{
	WeaponComponentAsset = FSoftObjectPath(TEXT("/Script/Odyssey.CWeaponComponent_DataAsset'/Game/Components/DA_Weapon.DA_Weapon'"));

	PrimaryComponentTick.bCanEverTick = true;
}

void UCWeaponComponent::BindInput(UEnhancedInputComponent* InEnhancedInputComponent)
{
	CheckNull(InEnhancedInputComponent);

	if (UInputAction* sword = CHelpers::LoadSynchronous(WeaponComponentAsset->IA_Sword))
	{
		InEnhancedInputComponent->BindAction(sword, ETriggerEvent::Started, this, &UCWeaponComponent::SetSwordMode);
	}

	if (UInputAction* attack = CHelpers::LoadSynchronous(WeaponComponentAsset->IA_Attack))
	{
		InEnhancedInputComponent->BindAction(attack, ETriggerEvent::Started, this, &UCWeaponComponent::OnAttack);
	}
}

ACWeapon_Attachment* UCWeaponComponent::GetAttachment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(WeaponDatas[(int32)WeaponType], nullptr);

	return WeaponDatas[(int32)WeaponType]->GetAttachment();
}

UCWeapon_EquipManager* UCWeaponComponent::GetEquipManager()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(WeaponDatas[(int32)WeaponType], nullptr);

	return WeaponDatas[(int32)WeaponType]->GetEquipManager();
}

void UCWeaponComponent::End_Unequip()
{
	ChangeType(EWeaponType::Max);
}

void UCWeaponComponent::SetUnarmedMode()
{
	GetEquipManager()->Unequip();
}

void UCWeaponComponent::SetSwordMode()
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

void UCWeaponComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CDebug::Screen(IsUnarmedMode() ? TEXT("Unarmed") : TEXT("Sword"), -1, 0.01f);
}

bool UCWeaponComponent::IsIdleState() const
{
	return OwnerCharacter->GetComponentByClass<UCStateComponent>()->IsIdleState();
}

void UCWeaponComponent::SetWeaponType(EWeaponType InNewWeaponType)
{
	if (WeaponType == InNewWeaponType)
	{
		SetUnarmedMode();

		return;
	}
	else if (IsUnarmedMode() == false)
	{
		GetEquipManager()->Unequip();
	}

	if (WeaponDatas[(int32)InNewWeaponType])
	{
		WeaponDatas[(int32)InNewWeaponType]->GetEquipManager()->Equip();

		ChangeType(InNewWeaponType);
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
	SetSwordMode();
}
