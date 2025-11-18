#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CMappingContextAsset.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;

UENUM(BlueprintType)
enum class EMappingContext : uint8
{
	Locomotion = 0,
	Combat,
	Max
};

UCLASS()
class ODYSSEY_API UCMappingContextAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UCMappingContextAsset();

	void OnPossess(UEnhancedInputLocalPlayerSubsystem* InSubsystem);

private:
	UPROPERTY(EditAnywhere, Category = "InputMappingContext")
	TObjectPtr<UInputMappingContext> MappingContexts[(int32)EMappingContext::Max];
};
