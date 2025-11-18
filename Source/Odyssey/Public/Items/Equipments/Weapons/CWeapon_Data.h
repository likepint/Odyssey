#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeapon_Data.generated.h"

class ACWeapon_Attachment;
class UCWeapon_EquipManager;

UCLASS()
class ODYSSEY_API UCWeapon_Data : public UObject
{
	GENERATED_BODY()

	friend class UCWeapon_DataAsset;

public:
	FORCEINLINE ACWeapon_Attachment* GetAttachment() { return Attachment; }
	FORCEINLINE UCWeapon_EquipManager* GetEquipManager() { return EquipManager; }

private:
	UPROPERTY()
	TObjectPtr<ACWeapon_Attachment> Attachment;

	UPROPERTY()
	TObjectPtr<UCWeapon_EquipManager> EquipManager;
};
