#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBindInput.generated.h"

class UEnhancedInputComponent;

UINTERFACE(MinimalAPI)
class UIBindInput : public UInterface
{
	GENERATED_BODY()
};

class ODYSSEY_API IIBindInput
{
	GENERATED_BODY()

public:
	virtual void BindInput(UEnhancedInputComponent* InEnhancedInputComponent) = 0;
};
