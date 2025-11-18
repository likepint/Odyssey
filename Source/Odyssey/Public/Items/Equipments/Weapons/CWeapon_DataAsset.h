#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Items/Equipments/Weapons/CWeapon_Structures.h"
#include "CWeapon_DataAsset.generated.h"

class ACCharacter;
class UCWeapon_Data;

class ACWeapon_Attachment;
class UCWeapon_EquipManager;

UCLASS()
class ODYSSEY_API UCWeapon_DataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UCWeapon_DataAsset();

	void BeginPlay(ACCharacter* InOwner, TObjectPtr<UCWeapon_Data>& OutWeaponData);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACWeapon_Attachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
	FEquipData EquipData;

	UPROPERTY(EditAnywhere)
	FUnequipData UnequipData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCWeapon_EquipManager> EquipManagerClass;
};
