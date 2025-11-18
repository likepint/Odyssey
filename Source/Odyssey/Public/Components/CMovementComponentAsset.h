#pragma once

#include "CoreMinimal.h"
#include "CMovementComponent.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "CMovementComponentAsset.generated.h"

class UAnimMontage;
class ACCharacter;

class UCMovementComponent;
class UEnhancedInputComponent;
class UInputAction;

UENUM(BlueprintType)
enum class EMovementInputAction : uint8
{
	Movement = 0,
	Crouch,
	Sprint,
	Walk,
	Look,
	Dodge,
	Max
};

USTRUCT()
struct FDodgeData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	void PlayDodgeMontage(ACCharacter* InOwnerCharacter);
};

UCLASS()
class ODYSSEY_API UCMovementComponentAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE FDodgeData& GetDodgeData() { return DodgeData; };

	UCMovementComponentAsset();

	void BindInput(UCMovementComponent* InMovementComponent, UEnhancedInputComponent* InEnhancedInputComponent);

private:
	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> InputActions[(int32)EMovementInputAction::Max];

	UPROPERTY(EditAnywhere, Category = "Dodge Data")
	FDodgeData DodgeData;
};
