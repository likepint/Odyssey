#pragma once

#include "CoreMinimal.h"

class ODYSSEY_API CDebug
{
public:
	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);
	static void Log(const UObject* InValue);
	static void Log(const FString& InFileName, const FString& InFuncName, int32 InLineNumber);

	static void Screen(int32 InValue, int32 InKey = -1, float InDuration = 1, FColor InColor = FColor::Cyan);
	static void Screen(float InValue, int32 InKey = -1, float InDuration = 1, FColor InColor = FColor::Cyan);
	static void Screen(const FString& InValue, int32 InKey = -1, float InDuration = 1, FColor InColor = FColor::Cyan);
	static void Screen(const FVector& InValue, int32 InKey = -1, float InDuration = 1, FColor InColor = FColor::Cyan);
	static void Screen(const FRotator& InValue, int32 InKey = -1, float InDuration = 1, FColor InColor = FColor::Cyan);
	static void Screen(const UObject* InValue, int32 InKey = -1, float InDuration = 1, FColor InColor = FColor::Cyan);
	static void Screen(const FString& InFileName, const FString& InFuncName, int32 InLineNumber);
};
