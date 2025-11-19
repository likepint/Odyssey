#pragma once

#include "CoreMinimal.h"
#include "Components/CComponent.h"
#include "CStatusComponent.generated.h"

UCLASS()
class ODYSSEY_API UCStatusComponent : public UCComponent
{
	GENERATED_BODY()

public:	
	FORCEINLINE const float& GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE const float& GetCurHealth() const { return CurHealth; }

	FORCEINLINE const float& GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE const float& GetCurStamina() const { return CurStamina; }
	
	FORCEINLINE bool IsDead() const { return CurHealth <= 0.0f; }

	void Damage(const float& InAmount);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxHealth = 100;
	
	float CurHealth;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxStamina = 100;

	float CurStamina;
};
