#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "CCharacter.generated.h"

/**
 *	Odyssey 프로젝트 캐릭터 클래스의 부모 클래스
 */

struct FDamageEvent;
class AController;

class UCStateComponent;
class UCMovementComponent;
class UCStatusComponent;
class UCWeaponComponent;

UCLASS(Abstract, NotBlueprintable)
class ODYSSEY_API ACCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	uint8 TeamID = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCStateComponent> StateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCMovementComponent> MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCStatusComponent> StatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCWeaponComponent> WeaponComponent;

private:
	struct FDamageData
	{
		ACCharacter* Character;
		float Power;
		AActor* Causer;

		struct FAttackDamageEvent* Event;
	} DamageData;
};
