#include "Items/Equipments/Weapons/CWeapon_Structures.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CMovementComponent.h"

void FAttackData::Attack(ACCharacter* InOwnerCharacter)
{
	if (TObjectPtr<UCMovementComponent> movement = InOwnerCharacter->GetComponentByClass<UCMovementComponent>())
	{
		movement->SetMovable(bMovable);
		movement->SetRotatable(bRotatable);
	}

	if (AttackMontage)
		InOwnerCharacter->PlayAnimMontage(AttackMontage, PlayRate);
}

void FDamagedData::SendDamage(ACCharacter* InAttacker, AActor* InAttackCauser, ACCharacter* InOther)
{
	FAttackDamageEvent e;
	e.HitData = this;

	InOther->TakeDamage(Power, e, InAttacker->GetController(), InAttackCauser);
}

void FDamagedData::PlayMontage(ACCharacter* InOwnerCharacter)
{
	if (DamagedMontage)
		InOwnerCharacter->PlayAnimMontage(DamagedMontage, PlayRate);
}

void FDamagedData::PlayHitStop(UWorld* InWorld)
{
	CheckTrue(FMath::IsNearlyZero(StopTime));

	TArray<ACCharacter*> characters;
	for (TObjectPtr<AActor> actor : InWorld->GetCurrentLevel()->Actors)
	{
		if (TObjectPtr<ACCharacter> character = Cast<ACCharacter>(actor))
		{
			character->CustomTimeDilation = 1e-3f;

			characters.Add(character);
		}
	}

	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([=]()
	{
		for (TObjectPtr<ACCharacter> character : characters)
			character->CustomTimeDilation = 1;
	});

	FTimerHandle timerHandle;
	InWorld->GetTimerManager().SetTimer(timerHandle, timerDelegate, StopTime, false);
}
