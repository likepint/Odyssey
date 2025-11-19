#pragma once

#include "CoreMinimal.h"
#include "Items/Equipments/Weapons/CWeapon_AttackManager.h"
#include "CAttackManager_Combo.generated.h"

class ACCharacter;

UCLASS()
class ODYSSEY_API UCAttackManager_Combo : public UCWeapon_AttackManager
{
	GENERATED_BODY()

public:
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

	virtual void Attack() override;
	virtual void Begin_Attack() override;
	virtual void End_Attack() override;
	
	virtual void OnAttachmentBeginOverlap(ACCharacter* InAttacker, AActor* InAttackCauser, ACCharacter* InOther) override;
	virtual void OnAttachmentEndCollision() override;

private:
	int32 Index;

	bool bEnable;
	bool bExist;

	float Angle = -2.0f;

	TArray<TObjectPtr<ACCharacter>> Victims;
};
