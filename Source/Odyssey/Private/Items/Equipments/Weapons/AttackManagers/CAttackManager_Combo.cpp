#include "Items/Equipments/Weapons/AttackManagers/CAttackManager_Combo.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CStateComponent.h"

void UCAttackManager_Combo::Attack()
{
	CheckTrue(AttackDatas.IsEmpty());

	if (bEnable)
	{
		bEnable = false;
		bExist = true;

		return;
	}

	CheckFalse(StateComponent->IsIdleState());

	Super::Attack();
	
	AttackDatas[Index].Attack(OwnerCharacter);
}

void UCAttackManager_Combo::Begin_Attack()
{
	Super::Begin_Attack();
	
	CheckFalse(bExist);

	bExist = false;
	AttackDatas[++Index].Attack(OwnerCharacter);
}

void UCAttackManager_Combo::End_Attack()
{
	Super::End_Attack();
	
	Index = 0;
}

void UCAttackManager_Combo::OnAttachmentBeginOverlap(ACCharacter* InAttacker, AActor* InAttackCauser, ACCharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOther);

	CheckNull(InOther);
	
	for (TObjectPtr<ACCharacter> victim : Victims)
		CheckTrue(victim == InOther);

	Victims.AddUnique(InOther);

	CheckTrue(DamagedDatas.Num() - 1 < Index);
	
	DamagedDatas[Index].SendDamage(InAttacker, InAttackCauser, InOther);
}

void UCAttackManager_Combo::OnAttachmentEndCollision()
{
	Super::OnAttachmentEndCollision();

	TObjectPtr<ACCharacter> candidate = nullptr;

	for (TObjectPtr<ACCharacter> victim : Victims)
	{
		FVector direction = victim->GetActorLocation() - OwnerCharacter->GetActorLocation();

		FVector forward = FQuat(OwnerCharacter->GetActorRotation()).GetForwardVector();

		float dot = FVector::DotProduct(direction.GetSafeNormal(), forward);
		if (dot >= Angle)
		{
			Angle = dot;
			candidate = victim;
		}
	}

	if (candidate)
	{
		FRotator rotator = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), candidate->GetActorLocation());
		FRotator target = FRotator(0, rotator.Yaw, 0);

		AController* controller = OwnerCharacter->GetController<AController>();
		controller->SetControlRotation(target);
	}

	Victims.Empty();
}
