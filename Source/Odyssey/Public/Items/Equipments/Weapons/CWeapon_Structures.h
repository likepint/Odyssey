#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeapon_Structures.generated.h"

class UAnimMontage;

USTRUCT()
struct FEquipData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> Montage;

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
	TObjectPtr<UAnimMontage> Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bMovable = true;

	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = false;
};

UCLASS()
class ODYSSEY_API UCWeapon_Structures : public UObject
{
	GENERATED_BODY()
};
