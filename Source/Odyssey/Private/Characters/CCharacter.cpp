#include "Characters/CCharacter.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"

ACCharacter::ACCharacter(const FObjectInitializer& ObjectInitializer)
{
	// UserControllerRotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Mesh
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.f, 0.0f));

	TObjectPtr<USkeletalMesh> mesh;
	CHelpers::GetAsset<USkeletalMesh>(mesh, TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	GetMesh()->SetSkeletalMesh(mesh);
	
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

	{ // LeaderPoseComponent
		TArray<USceneComponent*> children;
		GetMesh()->GetChildrenComponents(false, children);

		for (TObjectPtr<USceneComponent> child : children)
		{
			if (TObjectPtr<USkinnedMeshComponent> skinned = Cast<USkinnedMeshComponent>(child))
				skinned->SetLeaderPoseComponent(GetMesh());
		}
	}
}
