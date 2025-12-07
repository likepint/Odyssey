#pragma once

#include "CoreMinimal.h"

class ODYSSEY_API CDebug
{
public:
	static void Log(const int32 InValue);
	static void Log(const float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);
	static void Log(const UObject* InValue);
	static void Log(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber);

	static void Screen(const int32 InValue, const int32 InKey = -1, const float InDuration = 1, const FColor InColor = FColor::Cyan);
	static void Screen(const float InValue, const int32 InKey = -1, const float InDuration = 1, const FColor InColor = FColor::Cyan);
	static void Screen(const FString& InValue, const int32 InKey = -1, const float InDuration = 1, const FColor InColor = FColor::Cyan);
	static void Screen(const FVector& InValue, const int32 InKey = -1, const float InDuration = 1, const FColor InColor = FColor::Cyan);
	static void Screen(const FRotator& InValue, const int32 InKey = -1, const float InDuration = 1, const FColor InColor = FColor::Cyan);
	static void Screen(const UObject* InValue, const int32 InKey = -1, const float InDuration = 1, const FColor InColor = FColor::Cyan);
	static void Screen(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber);
};
