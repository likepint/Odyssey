#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items/Equipments/Weapons/CWeapon_Structures.h"
#include "CWeapon_AttackManager.generated.h"

class ACWeapon_Attachment;
class UCWeapon_EquipManager;
class ACCharacter;

class UCStateComponent;
class UCMovementComponent;

UCLASS()
class ODYSSEY_API UCWeapon_AttackManager : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE const bool& GetBeginAttack() const { return bBeginAttack; }
	FORCEINLINE const bool& GetInAttacking() const { return bInAttacking; }

	virtual void BeginPlay(ACWeapon_Attachment* InAttachment, UCWeapon_EquipManager* InEquipManager, ACCharacter* InOwnerCharacter, const TArray<FAttackData>& InAttackDatas, const TArray<FDamagedData>& InDamagedDatas);

	UFUNCTION()
	virtual void OnBeginEquip() {}

	UFUNCTION()
	virtual void OnBeginUnequip() {}

	virtual void Attack();
	virtual void Begin_Attack();
	virtual void End_Attack();

	UFUNCTION()
	virtual void OnAttachmentBeginCollision() {}

	UFUNCTION()
	virtual void OnAttachmentEndCollision() {}

	UFUNCTION()
	virtual void OnAttachmentBeginOverlap(ACCharacter* InAttacker, AActor* InAttackCauser, ACCharacter* InOther) {}

	UFUNCTION()
	virtual void OnAttachmentEndOverlap(ACCharacter* InAttacker, ACCharacter* InOther) {}

protected:
	bool bInAttacking = false;
	bool bBeginAttack = false;

	UPROPERTY()
	TObjectPtr<ACCharacter> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<UCStateComponent> StateComponent;

	UPROPERTY()
	TObjectPtr<UCMovementComponent> MovementComponent;

	TArray<FAttackData> AttackDatas;
	TArray<FDamagedData> DamagedDatas;
};
