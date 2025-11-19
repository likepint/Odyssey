#include "Items/Equipments/Weapons/CWeapon_AttackManager.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"

void UCWeapon_AttackManager::BeginPlay(ACWeapon_Attachment* InAttachment, UCWeapon_EquipManager* InEquipManager, ACCharacter* InOwnerCharacter, const TArray<FAttackData>& InAttackDatas, const TArray<FDamagedData>& InDamagedDatas)
{
	OwnerCharacter = InOwnerCharacter;

	StateComponent = InOwnerCharacter->GetComponentByClass<UCStateComponent>();
	MovementComponent = InOwnerCharacter->GetComponentByClass<UCMovementComponent>();

	AttackDatas = InAttackDatas;
	DamagedDatas = InDamagedDatas;
}

void UCWeapon_AttackManager::Attack()
{
	bInAttacking = true;

	StateComponent->SetAttackingState();
}

void UCWeapon_AttackManager::Begin_Attack()
{
	bBeginAttack = true;
}

void UCWeapon_AttackManager::End_Attack()
{
	bInAttacking = false;
	bBeginAttack = false;

	CheckNull(StateComponent);
	StateComponent->SetIdleState();

	CheckNull(MovementComponent);
	MovementComponent->SetMovable(true);
	MovementComponent->SetRotatable(false);
}
