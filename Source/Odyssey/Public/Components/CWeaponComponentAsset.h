#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CWeaponComponentAsset.generated.h"

class UCWeaponComponent;
class UEnhancedInputComponent;
class UInputAction;

UENUM(BlueprintType)
enum class EWeaponInputAction : uint8
{
	Sword = 0,
	Attack,
	Max
};

UCLASS()
class ODYSSEY_API UCWeaponComponentAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UCWeaponComponentAsset();

	void BindInput(UCWeaponComponent* InWeaponComponent, UEnhancedInputComponent* InEnhancedInputComponent);
	
private:
	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> InputActions[(int32)EWeaponInputAction::Max];
};
