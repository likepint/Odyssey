#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class ACPlayerController;

class UCStateComponent;
class UCWeaponComponent;
class UCStatusComponent;

struct FCategoryData
{
	bool bDraw = false;
	FString ActorName = "";
	FVector ActorLocation = FVector::ZeroVector;
	float Speed = 0.0f;
	FString StateType = "";
	FString WeaponType = "";
	float CurHealth = 0.0f;
	float CurStamina = 0.0f;
};

class DEBUGGINGTOOLS_API DebuggerCategory : public FGameplayDebuggerCategory
{
public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();
	
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

private:
	FCategoryData PlayerPawnData;
	
	DebuggerCategory();
};
