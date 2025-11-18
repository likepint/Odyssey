#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon_Attachment.generated.h"

class USceneComponent;
class ACCharacter;
class UShapeComponent;

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

	void OnCollisions();
	void OffCollisions();

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
