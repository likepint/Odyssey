#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items/Equipments/Weapons/CWeapon_Structures.h"
#include "CWeapon_EquipManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentBeginEquip);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentBeginUnequip);

class ACCharacter;
struct FEquipData;
struct FUnequipData;

class UCStateComponent;
class UCMovementComponent;

UCLASS()
class ODYSSEY_API UCWeapon_EquipManager : public UObject
{
	GENERATED_BODY()

public:
	const FEquipData& GetEquipData() const { return EquipData; };

	const FUnequipData& GetUnequipData() const { return UnequipData; };

	FORCEINLINE const bool& GetBeginEquip() const { return bBeginEquip; }

	FORCEINLINE const bool* GetEquipped() { return &bEquipped; }

	void BeginPlay(ACCharacter* InOwner, const FEquipData& InEquipData, const FUnequipData& InUnequipData);

	FEquipmentBeginEquip OnEquipmentBeginEquip;
	FEquipmentBeginUnequip OnEquipmentBeginUnequip;

	UFUNCTION(BlueprintNativeEvent)
	void Equip();

	UFUNCTION(BlueprintNativeEvent)
	void Begin_Equip();

	UFUNCTION(BlueprintNativeEvent)
	void End_Equip();

	UFUNCTION(BlueprintNativeEvent)
	void ImmediatelyEquip();

	UFUNCTION(BlueprintNativeEvent)
	void Unequip();

	UFUNCTION(BlueprintNativeEvent)
	void End_Unequip();
	
	UFUNCTION(BlueprintNativeEvent)
	void ImmediatelyUnequip();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ACCharacter> OwnerCharacter;

private:
	UPROPERTY()
	TObjectPtr<UCStateComponent> StateComponent;

	UPROPERTY()
	TObjectPtr<UCMovementComponent> MovementComponent;

	FEquipData EquipData;
	FUnequipData UnequipData;

	bool bBeginEquip;
	bool bEquipped;
};
