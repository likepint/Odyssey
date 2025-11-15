#include "Components/CComponent.h"
#include "Global.h"
#include "Characters/CCharacter.h"

UCComponent::UCComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACCharacter>(GetOwner());
	CheckNull(OwnerCharacter);
}
