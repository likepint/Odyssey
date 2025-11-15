#include "Characters/CCharacter.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"

ACCharacter::ACCharacter(const FObjectInitializer& ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.f, 0.0f));

	// StateComponent
	StateComponent = CreateDefaultSubobject<UCStateComponent>(TEXT("StateComponent"));

	// MovementComponent
	MovementComponent = CreateDefaultSubobject<UCMovementComponent>(TEXT("MovementComponent"));
	
	PrimaryActorTick.bCanEverTick = true;
}

void ACCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	TArray<USceneComponent*> children;
	GetMesh()->GetChildrenComponents(false, children);

	for (USceneComponent* child : children)
	{
		if (USkinnedMeshComponent* skinned = Cast<USkinnedMeshComponent>(child))
			skinned->SetLeaderPoseComponent(GetMesh());
	}
}
