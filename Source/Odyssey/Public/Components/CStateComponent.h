#pragma once

#include "CoreMinimal.h"
#include "Components/CComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle = 0,
	Equipping,
	Attacking,
	Damaged,
	Dodge,
	Parkour,
	Dead,
	Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevStateType, EStateType, InNewStateType);

UCLASS()
class ODYSSEY_API UCStateComponent : public UCComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE const EStateType& GetStateType() const { return StateType; }
	
	FORCEINLINE bool IsIdleState() const { return StateType == EStateType::Idle; }
	FORCEINLINE bool IsEquippingState() const { return StateType == EStateType::Equipping; }
	FORCEINLINE bool IsAttackingState() const { return StateType == EStateType::Attacking; }
	FORCEINLINE bool IsDamagedState() const { return StateType == EStateType::Damaged; }
	FORCEINLINE bool IsDodgeState() const { return StateType == EStateType::Dodge; }
	FORCEINLINE bool IsParkourState() const { return StateType == EStateType::Parkour; }
	FORCEINLINE bool IsDeadState() const { return StateType == EStateType::Dead; }

	void SetIdleState();
	void SetEquippingState();
	void SetAttackingState();
	void SetDamagedState();
	void SetDodgeState();
	void SetParkourState();
	void SetDeadState();

	FStateTypeChanged OnStateTypeChanged;

private:
	UPROPERTY(VisibleAnywhere, Category = "State")
	EStateType StateType = EStateType::Idle;

	void ChangeType(EStateType InNewStateType);
};
