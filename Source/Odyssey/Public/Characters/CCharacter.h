#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

UCLASS()
class ODYSSEY_API ACCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
