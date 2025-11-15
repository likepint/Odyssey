#include "AnimNotifies/CAnimNotify_EndState.h"
#include "Global.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_EndState::GetNotifyName_Implementation() const
{
	return "End State";
}

void UCAnimNotify_EndState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCStateComponent* state = MeshComp->GetOwner()->GetComponentByClass<UCStateComponent>();
	CheckNull(state);

	state->SetIdleState();
}
