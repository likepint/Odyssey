#pragma once

#include "CoreMinimal.h"
#include "Components/CComponent.h"
#include "Interfaces/IBindInput.h"
#include "CMovementComponent.generated.h"

class UEnhancedInputComponent;

class UCMovementComponentAsset;

struct FInputActionValue;

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Idle = 0,
	CrouchedWalk,
	CrouchedRun,
	StandingWalk,
	StandingRun,
	StandingSprint,
	Max
};

UCLASS()
class ODYSSEY_API UCMovementComponent : public UCComponent, public IIBindInput
{
	GENERATED_BODY()

	friend class UCMovementComponentAsset;

public:
	FORCEINLINE bool IsCrouched() const { return bCrouched; }

	UCMovementComponent();

	virtual void BindInput(UEnhancedInputComponent* InEnhancedInputComponent) override;

	void SetTargetSpeed(ESpeedType InType);

	void SetMovable(bool bInMovable);
	void SetRotatable(bool bInRotatable);
	void SetControlRotation(bool bInControlRotation);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	TObjectPtr<UCMovementComponentAsset> MovementComponentAsset;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
	TArray<float> Speed = {0, 100, 250, 200, 400, 500};

	bool bMovable = true;

	bool bCrouched = false;

	bool bWantsToRun = false;
	bool bWantsToWalk = false;
	bool bWantsToSprint = false;

	float TargetSpeed = 0.0f;
	float TargetSpeedInterpRate = 2.5f;

	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	FVector2D Sensitivity = FVector2D(45.0f, 45.0f);

	bool bRotatable = true;

	void SetMaxWalkSpeed(const float& InDeltaTime);

	void OnMovement(const FInputActionValue& InValue);
	void OffMovement(const FInputActionValue& InValue);

	void OnCrouch(const FInputActionValue& InValue);

	void OnWalk(const FInputActionValue& InValue);
	void OffWalk(const FInputActionValue& InValue);

	void OnSprint(const FInputActionValue& InValue);

	void OnLook(const FInputActionValue& InValue);

	void OnDodge(const FInputActionValue& InValue);
};
