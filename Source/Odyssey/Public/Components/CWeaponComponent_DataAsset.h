#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CWeaponComponent_DataAsset.generated.h"

class UInputAction;

UCLASS()
class ODYSSEY_API UCWeaponComponent_DataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TSoftObjectPtr<UInputAction> IA_Sword;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TSoftObjectPtr<UInputAction> IA_Attack;

	UCWeaponComponent_DataAsset();
};
