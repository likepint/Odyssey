#include "Characters/CCharacter.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
}
