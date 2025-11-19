#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeapon_Data.generated.h"

class ACWeapon_Attachment;
class UCWeapon_EquipManager;
class UCWeapon_AttackManager;

UCLASS()
class ODYSSEY_API UCWeapon_Data : public UObject
{
	GENERATED_BODY()

	friend class UCWeapon_DataAsset;

public:
	FORCEINLINE TObjectPtr<ACWeapon_Attachment> GetAttachment() { return Attachment; }
	FORCEINLINE TObjectPtr<UCWeapon_EquipManager> GetEquipManager() { return EquipManager; }
	FORCEINLINE TObjectPtr<UCWeapon_AttackManager> GetAttackManager() { return AttackManager; }

private:
	UPROPERTY()
	TObjectPtr<ACWeapon_Attachment> Attachment;

	UPROPERTY()
	TObjectPtr<UCWeapon_EquipManager> EquipManager;

	UPROPERTY()
	TObjectPtr<UCWeapon_AttackManager> AttackManager;
};
