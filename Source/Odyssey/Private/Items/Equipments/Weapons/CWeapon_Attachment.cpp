#include "Items/Equipments/Weapons/CWeapon_Attachment.h"
#include "Global.h"
#include "Components/SceneComponent.h"
#include "Characters/CCharacter.h"
#include "Components/ShapeComponent.h"

ACWeapon_Attachment::ACWeapon_Attachment()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
}

void ACWeapon_Attachment::OnCollisions()
{
	for (TObjectPtr<UShapeComponent> shape : Collisions)
		shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACWeapon_Attachment::OffCollisions()
{
	for (TObjectPtr<UShapeComponent> shape : Collisions)
		shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACWeapon_Attachment::BeginPlay()
{
	OwnerCharacter = Cast<ACCharacter>(GetOwner());

	// Collisions
	TArray<USceneComponent*> children;
	SceneComponent->GetChildrenComponents(true, children);
	for (TObjectPtr<USceneComponent> child : children)
	{
		if (TObjectPtr<UPrimitiveComponent> mesh = Cast<UPrimitiveComponent>(child))
		{
			mesh->SetCollisionProfileName(TEXT("Weapon"));
			mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			if (TObjectPtr<UShapeComponent> shape = Cast<UShapeComponent>(mesh))
				Collisions.Add(shape);
		}
	}
	OffCollisions();

	Super::BeginPlay();
}

void ACWeapon_Attachment::AttachTo(FName InSocketName)
{
	CheckNull(OwnerCharacter);

	FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, true);
	AttachToComponent(OwnerCharacter->GetMesh(), rules, InSocketName);
}
