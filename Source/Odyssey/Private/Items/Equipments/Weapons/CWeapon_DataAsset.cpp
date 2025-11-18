#include "Items/Equipments/Weapons/CWeapon_DataAsset.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Items/Equipments/Weapons/CWeapon_Attachment.h"
#include "Items/Equipments/Weapons/CWeapon_EquipManager.h"
#include "Items/Equipments/Weapons/CWeapon_Data.h"

UCWeapon_DataAsset::UCWeapon_DataAsset()
{
	AttachmentClass = ACWeapon_Attachment::StaticClass();
	EquipManagerClass = UCWeapon_EquipManager::StaticClass();
}

void UCWeapon_DataAsset::BeginPlay(ACCharacter* InOwner, TObjectPtr<UCWeapon_Data>& OutWeaponData)
{
	TObjectPtr<ACWeapon_Attachment> attachment = nullptr;
	if (AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		attachment = InOwner->GetWorld()->SpawnActor<ACWeapon_Attachment>(AttachmentClass, params);
	}

	TObjectPtr<UCWeapon_EquipManager> equipManager = nullptr;
	if (EquipManagerClass)
	{
		equipManager = NewObject<UCWeapon_EquipManager>(this, EquipManagerClass);
		equipManager->BeginPlay(InOwner, EquipData, UnequipData);

		if (attachment)
		{
			equipManager->OnEquipmentBeginEquip.AddDynamic(attachment, &ACWeapon_Attachment::OnBeginEquip);
			equipManager->OnEquipmentBeginUnequip.AddDynamic(attachment, &ACWeapon_Attachment::OnBeginUnequip);
		}
	}

	OutWeaponData = NewObject<UCWeapon_Data>();
	(OutWeaponData)->Attachment = attachment;
	(OutWeaponData)->EquipManager = equipManager;
}
