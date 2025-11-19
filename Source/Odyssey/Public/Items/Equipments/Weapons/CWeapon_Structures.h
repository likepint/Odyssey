#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DamageEvents.h"
#include "CWeapon_Structures.generated.h"

class UAnimMontage;
class ACCharacter;

USTRUCT()
struct FEquipData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bMovable = true;

	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = false;
};

USTRUCT()
struct FUnequipData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> UnequipMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bMovable = true;

	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = false;
};

USTRUCT()
struct FAttackData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bMovable = true;

	UPROPERTY(EditAnywhere)
	bool bRotatable = false;

public:
	void Attack(ACCharacter* InOwnerCharacter);
};

USTRUCT()
struct FDamagedData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DamagedMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	float Power = 1.0f;

	UPROPERTY(EditAnywhere)
	float Launch = 100.0f;

	UPROPERTY(EditAnywhere)
	float StopTime = 0.0f;

public:
	void SendDamage(ACCharacter* InAttacker, AActor* InAttackCauser, ACCharacter* InOther);
	void PlayMontage(ACCharacter* InOwnerCharacter);
	void PlayHitStop(UWorld* InWorld);
};

USTRUCT()
struct FAttackDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	FDamagedData* HitData;
};

UCLASS()
class ODYSSEY_API UCWeapon_Structures : public UObject
{
	GENERATED_BODY()
};
