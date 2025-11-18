#include "Characters/Misthios/CCharacter_Misthios.h"
#include "Global.h"
#include "Components/CCharacterMovementComponent.h"
#include "Characters/CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

ACCharacter_Misthios::ACCharacter_Misthios(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCCharacterMovementComponent>(CharacterMovementComponentName))
{
	// AnimInstance
	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(animInstance, TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Misthios/ABP_CAnimInstance_Misthios.ABP_CAnimInstance_Misthios_C'"));
	GetMesh()->SetAnimInstanceClass(animInstance);

	// SpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bUsePawnControlRotation = true;

	// CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	PrimaryActorTick.bCanEverTick = true;
}

void ACCharacter_Misthios::BeginPlay()
{
	Super::BeginPlay();
	
	{ // Collisions
		TObjectPtr<UCapsuleComponent> root = Cast<UCapsuleComponent>(GetRootComponent());
		root->SetCollisionProfileName(TEXT("Misthios"));
		root->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		TArray<USceneComponent*> children;
		root->GetChildrenComponents(true, children);
		for (TObjectPtr<USceneComponent> child : children)
		{
			if (TObjectPtr<UPrimitiveComponent> mesh = Cast<UPrimitiveComponent>(child))
			{
				mesh->SetCollisionProfileName(TEXT("Misthios"));
				mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
	}
}
