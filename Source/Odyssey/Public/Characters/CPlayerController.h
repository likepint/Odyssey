#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class ODYSSEY_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UInputMappingContext> IMC_Locomotion;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UInputMappingContext> IMC_Combat;
	
	virtual void OnPossess(APawn* InPawn) override;
};
