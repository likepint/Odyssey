#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CComponent.generated.h"

class ACCharacter;

UCLASS(ClassGroup=(Custom))
class ODYSSEY_API UCComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ACCharacter> OwnerCharacter;
	
	virtual void BeginPlay() override;
};
