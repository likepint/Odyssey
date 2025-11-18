#pragma once

#include "CoreMinimal.h"
#include "Components/CComponent.h"
#include "Interfaces/IBindInput.h"
#include "CWeaponComponent.generated.h"

class UEnhancedInputComponent;

class ACWeapon_Attachment;
class UCWeapon_EquipManager;

class UCWeapon_DataAsset;
class UCWeapon_Data;
struct FInputActionValue;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword = 0,
	Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevWeaponType, EWeaponType, InNewWeaponType);

UCLASS()
class ODYSSEY_API UCWeaponComponent : public UCComponent, public IIBindInput
{
	GENERATED_BODY()

	friend class UCWeaponComponentAsset;

public:
	FORCEINLINE bool IsUnarmedMode() const { return WeaponType == EWeaponType::Max; }
	FORCEINLINE bool IsSwordMode() const { return WeaponType == EWeaponType::Sword; }

	UCWeaponComponent();

	virtual void BindInput(UEnhancedInputComponent* InEnhancedInputComponent) override;

	FWeaponTypeChanged OnWeaponTypeChange;

	ACWeapon_Attachment* GetAttachment();
	UCWeapon_EquipManager* GetEquipManager();
	
	void End_Unequip();

	void OnUnarmedMode();
	void OnSwordMode();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	TObjectPtr<UCWeaponComponentAsset> WeaponComponentAsset;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	TObjectPtr<UCWeapon_DataAsset> WeaponAssets[(int32)EWeaponType::Max];

	UPROPERTY()
	TObjectPtr<UCWeapon_Data> WeaponDatas[(int32)EWeaponType::Max];

	EWeaponType WeaponType = EWeaponType::Max;

	bool IsIdleState() const;

	void SetWeaponType(EWeaponType InNewWeaponType);
	void ChangeType(EWeaponType InNewWeaponType);

	void OnAttack(const FInputActionValue& InValue);
};
