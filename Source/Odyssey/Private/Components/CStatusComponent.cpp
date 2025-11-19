#include "Components/CStatusComponent.h"

void UCStatusComponent::Damage(const float& InAmount)
{
	CurHealth += (InAmount * -1.0f);
	CurHealth = FMath::Clamp(CurHealth, 0.0f, MaxHealth);
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurHealth = MaxHealth;
	CurStamina = MaxStamina;
}
