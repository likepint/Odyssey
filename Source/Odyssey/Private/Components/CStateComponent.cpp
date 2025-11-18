#include "Components/CStateComponent.h"

void UCStateComponent::SetIdleState()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetEquippingState()
{
	ChangeType(EStateType::Equipping);
}

void UCStateComponent::SetAttackingState()
{
	ChangeType(EStateType::Attacking);
}

void UCStateComponent::SetDamagedState()
{
	ChangeType(EStateType::Damaged);
}

void UCStateComponent::SetDodgeState()
{
	ChangeType(EStateType::Dodge);
}

void UCStateComponent::SetParkourState()
{
	ChangeType(EStateType::Parkour);
}

void UCStateComponent::SetDeadState()
{
	ChangeType(EStateType::Dead);
}

void UCStateComponent::ChangeType(EStateType InNewStateType)
{
	EStateType prevStateType = StateType;
	StateType = InNewStateType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prevStateType, StateType);
}
