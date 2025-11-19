#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon_Attachment.generated.h"

class USceneComponent;
class ACCharacter;
class UShapeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentBeginCollision);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentEndCollision);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, ACCharacter*, InAttacker, AActor*, InAttackCauser, ACCharacter*, InOther);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttachmentEndOverlap, ACCharacter*, InAttacker, ACCharacter*, InOther);

UCLASS()
class ODYSSEY_API ACWeapon_Attachment : public AActor
{
	GENERATED_BODY()

public:
	ACWeapon_Attachment();

	UFUNCTION(BlueprintNativeEvent)
	void OnBeginEquip();
	virtual void OnBeginEquip_Implementation() {};

	UFUNCTION(BlueprintNativeEvent)
	void OnBeginUnequip();
	virtual void OnBeginUnequip_Implementation() {};

	FAttachmentBeginCollision OnAttachmentBeginCollision;
	FAttachmentEndCollision OnAttachmentEndCollision;

	void OnCollisions();
	void OffCollisions();

	FAttachmentBeginOverlap OnAttachmentBeginOverlap;
	FAttachmentEndOverlap OnAttachmentEndOverlap;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ACCharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	TArray<TObjectPtr<UShapeComponent>> Collisions;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AttachTo(FName InSocketName);
};
