#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

/**
 *	Odyssey 프로젝트 캐릭터 클래스의 부모 클래스
 */

class UCStateComponent;
class UCMovementComponent;
class UCWeaponComponent;

UCLASS(Abstract, NotBlueprintable)
class ODYSSEY_API ACCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCStateComponent> StateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCMovementComponent> MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCWeaponComponent> WeaponComponent;
};
