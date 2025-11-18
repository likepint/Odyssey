#include "Characters/CCharacter.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"

ACCharacter::ACCharacter(const FObjectInitializer& ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.f, 0.0f));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	if (mesh.Object)
		GetMesh()->SetSkeletalMesh(mesh.Object);

	// StateComponent
	StateComponent = CreateDefaultSubobject<UCStateComponent>(TEXT("StateComponent"));

	// MovementComponent
	MovementComponent = CreateDefaultSubobject<UCMovementComponent>(TEXT("MovementComponent"));

	// WeaponComponent
	WeaponComponent = CreateDefaultSubobject<UCWeaponComponent>(TEXT("WeaponComponent"));
	
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
