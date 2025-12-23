#pragma once

#include "CoreMinimal.h"

#define DISPLAY_LINE(){ CDebug::Display(__FILE__, __FUNCTION__, __LINE__); }
#define WARNING_LINE(){ CDebug::Warning(__FILE__, __FUNCTION__, __LINE__); }
#define ERROR_LINE(){ CDebug::Error(__FILE__, __FUNCTION__, __LINE__); }
#define SCREEN_LINE(){ CDebug::Screen(__FILE__, __FUNCTION__, __LINE__); }

class ODYSSEY_API CDebug
{
public:
	static void Display(const int32 InValue);
	static void Display(const float InValue);
	static void Display(const FString& InValue);
	static void Display(const FVector& InValue);
	static void Display(const FRotator& InValue);
	static void Display(const UObject* InValue);
	static void Display(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber);

	static void Warning(const int32 InValue);
	static void Warning(const float InValue);
	static void Warning(const FString& InValue);
	static void Warning(const FVector& InValue);
	static void Warning(const FRotator& InValue);
	static void Warning(const UObject* InValue);
	static void Warning(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber);

	static void Error(const int32 InValue);
	static void Error(const float InValue);
	static void Error(const FString& InValue);
	static void Error(const FVector& InValue);
	static void Error(const FRotator& InValue);
	static void Error(const UObject* InValue);
	static void Error(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber);

	static void Screen(const int32 InValue, const FColor InColor = FColor::Emerald, const float InDuration = 1.0f, const int32 InKey = -1);
	static void Screen(const float InValue, const FColor InColor = FColor::Emerald, const float InDuration = 1.0f, const int32 InKey = -1);
	static void Screen(const FString& InValue, const FColor InColor = FColor::Emerald, const float InDuration = 1.0f, const int32 InKey = -1);
	static void Screen(const FVector& InValue, const FColor InColor = FColor::Emerald, const float InDuration = 1.0f, const int32 InKey = -1);
	static void Screen(const FRotator& InValue, const FColor InColor = FColor::Emerald, const float InDuration = 1.0f, const int32 InKey = -1);
	static void Screen(const UObject* InValue, const FColor InColor = FColor::Emerald, const float InDuration = 1.0f, const int32 InKey = -1);
	static void Screen(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber, const FColor InColor = FColor::Emerald, const float InDuration = 1.0f, const int32 InKey = -1);
};
