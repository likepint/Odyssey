#include "AnimNotifies/CAnimNotify_Equip.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Items/Equipments/Weapons/CWeapon_EquipManager.h"

FString UCAnimNotify_Equip::GetNotifyName_Implementation() const
{
	return TEXT("Equip");
}

void UCAnimNotify_Equip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	
	TObjectPtr<UCWeaponComponent> weapon = MeshComp->GetOwner()->GetComponentByClass<UCWeaponComponent>();
	CheckNull(weapon);
	CheckNull(weapon->GetEquipManager());

	weapon->GetEquipManager()->Begin_Equip();
	weapon->GetEquipManager()->End_Equip();
}
