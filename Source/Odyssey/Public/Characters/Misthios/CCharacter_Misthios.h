#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "CCharacter_Misthios.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCMovementComponent;

UCLASS(Blueprintable)
class ODYSSEY_API ACCharacter_Misthios : public ACCharacter
{
	GENERATED_BODY()

public:
	ACCharacter_Misthios(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
};
