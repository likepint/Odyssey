#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UCMappingContextAsset;

UCLASS()
class ODYSSEY_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCMappingContextAsset> MappingContextAsset;
	
	virtual void OnPossess(APawn* InPawn) override;
};
