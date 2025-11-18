#include "Characters/CMappingContextAsset.h"
#include "Global.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

UCMappingContextAsset::UCMappingContextAsset()
{
	// Locomotion
	CHelpers::GetAsset<UInputMappingContext>(MappingContexts[(int32)EMappingContext::Locomotion], TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Locomotion.IMC_Locomotion'"));

	// Combat
	CHelpers::GetAsset<UInputMappingContext>(MappingContexts[(int32)EMappingContext::Combat], TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Combat.IMC_Combat'"));
}

void UCMappingContextAsset::OnPossess(UEnhancedInputLocalPlayerSubsystem* InSubsystem)
{
	for (int32 idx = 0; idx < (int32)EMappingContext::Max; ++idx)
	{
		if (MappingContexts[idx])
			InSubsystem->AddMappingContext(MappingContexts[idx], idx);
	}
}
