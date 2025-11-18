#include "Characters/Misthios/CCharacter_Misthios.h"
#include "Global.h"
#include "Components/CCharacterMovementComponent.h"
#include "Characters/CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACCharacter_Misthios::ACCharacter_Misthios(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCCharacterMovementComponent>(CharacterMovementComponentName))
{
	ConstructorHelpers::FClassFinder<UCAnimInstance> animInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Misthios/ABP_CAnimInstance_Misthios.ABP_CAnimInstance_Misthios_C'"));
	if (animInstance.Class)
		GetMesh()->SetAnimInstanceClass(animInstance.Class);
	
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
