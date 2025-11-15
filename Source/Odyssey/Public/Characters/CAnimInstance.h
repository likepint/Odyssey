#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

class ACCharacter;

UCLASS()
class ODYSSEY_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ACCharacter> OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed = 0.0f;

	FRotator PrevRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationInterpSpeed = 25.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Direction = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bMovable = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCrouched = false;

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
