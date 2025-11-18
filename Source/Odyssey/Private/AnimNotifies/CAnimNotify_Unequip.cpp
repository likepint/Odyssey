#include "AnimNotifies/CAnimNotify_Unequip.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Items/Equipments/Weapons/CWeapon_EquipManager.h"

FString UCAnimNotify_Unequip::GetNotifyName_Implementation() const
{
	return TEXT("Unequip");
}

void UCAnimNotify_Unequip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	TObjectPtr<UCWeaponComponent> weapon = MeshComp->GetOwner()->GetComponentByClass<UCWeaponComponent>();
	CheckNull(weapon);
	CheckNull(weapon->GetEquipManager());

	weapon->GetEquipManager()->End_Unequip();
	weapon->End_Unequip();
}
