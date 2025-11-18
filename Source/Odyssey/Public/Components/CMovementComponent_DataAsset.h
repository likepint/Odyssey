#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CMovementComponent_DataAsset.generated.h"

class UAnimMontage;
class ACCharacter;

class UInputAction;

USTRUCT()
struct FDodgeData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UAnimMontage> DodgeMontagePath;

	UPROPERTY()
	TObjectPtr<UAnimMontage> DodgeMontage;
	
	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	FDodgeData();
	void BeginPlay();
	void PlayDodgeMontage(ACCharacter* InOwnerCharacter);
};

UCLASS()
class ODYSSEY_API UCMovementComponent_DataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TSoftObjectPtr<UInputAction> IA_Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TSoftObjectPtr<UInputAction> IA_Crouch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TSoftObjectPtr<UInputAction> IA_Sprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TSoftObjectPtr<UInputAction> IA_Walk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TSoftObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TSoftObjectPtr<UInputAction> IA_Dodge;

	UPROPERTY(EditAnywhere, Category = "Dodge")
	FDodgeData DodgeData;

	UCMovementComponent_DataAsset();

	void BeginPlay();
};
