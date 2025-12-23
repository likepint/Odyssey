#include "Utilities/CDebug.h"

DEFINE_LOG_CATEGORY_STATIC(Odyssey, Display, All)

void CDebug::Display(const int32 InValue)
{
	UE_LOG(Odyssey, Display, L"%d", InValue);
}

void CDebug::Display(const float InValue)
{
	UE_LOG(Odyssey, Display, L"%f", InValue);
}

void CDebug::Display(const FString& InValue)
{
	UE_LOG(Odyssey, Display, L"%s", *InValue);
}

void CDebug::Display(const FVector& InValue)
{
	UE_LOG(Odyssey, Display, L"%s", *InValue.ToString());
}

void CDebug::Display(const FRotator& InValue)
{
	UE_LOG(Odyssey, Display, L"%s", *InValue.ToString());
}

void CDebug::Display(const UObject* InValue)
{
	FString String;

	if (InValue)
		String.Append(InValue->GetName());

	String.Append(InValue ? " isn't Null" : " is Null");

	UE_LOG(Odyssey, Display, L"%s", *String);
}

void CDebug::Display(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber)
{
	// C:\\Example\\Example.cpp

	int32 Index = 0;
	InFileName.FindLastChar(L'\\', Index);

	const int32 Length = InFileName.Len() - 1;
	const FString FileName = InFileName.Right(Length - Index);

	UE_LOG(Odyssey, Display, L"%s, %s, %d", *FileName, *InFuncName, InLineNumber);
}

void CDebug::Warning(const int32 InValue)
{
	UE_LOG(Odyssey, Warning, L"%d", InValue);
}

void CDebug::Warning(const float InValue)
{
	UE_LOG(Odyssey, Warning, L"%f", InValue);
}

void CDebug::Warning(const FString& InValue)
{
	UE_LOG(Odyssey, Warning, L"%s", *InValue);
}

void CDebug::Warning(const FVector& InValue)
{
	UE_LOG(Odyssey, Warning, L"%s", *InValue.ToString());
}

void CDebug::Warning(const FRotator& InValue)
{
	UE_LOG(Odyssey, Warning, L"%s", *InValue.ToString());
}

void CDebug::Warning(const UObject* InValue)
{
	FString String;

	if (InValue)
		String.Append(InValue->GetName());

	String.Append(InValue ? " isn't Null" : " is Null");

	UE_LOG(Odyssey, Warning, L"%s", *String);
}

void CDebug::Warning(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber)
{
	// C:\\Example\\Example.cpp

	int32 Index = 0;
	InFileName.FindLastChar(L'\\', Index);

	const int32 Length = InFileName.Len() - 1;
	const FString FileName = InFileName.Right(Length - Index);

	UE_LOG(Odyssey, Warning, L"%s, %s, %d", *FileName, *InFuncName, InLineNumber);
}

void CDebug::Error(const int32 InValue)
{
	UE_LOG(Odyssey, Error, L"%d", InValue);
}

void CDebug::Error(const float InValue)
{
	UE_LOG(Odyssey, Error, L"%f", InValue);
}

void CDebug::Error(const FString& InValue)
{
	UE_LOG(Odyssey, Error, L"%s", *InValue);
}

void CDebug::Error(const FVector& InValue)
{
	UE_LOG(Odyssey, Error, L"%s", *InValue.ToString());
}

void CDebug::Error(const FRotator& InValue)
{
	UE_LOG(Odyssey, Error, L"%s", *InValue.ToString());
}

void CDebug::Error(const UObject* InValue)
{
	FString Message;

	if (InValue)
		Message.Append(InValue->GetName());

	Message.Append(InValue ? " isn't Null" : " is Null");

	UE_LOG(Odyssey, Error, L"%s", *Message);
}

void CDebug::Error(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber)
{
	// C:\\Example\\Example.cpp

	int32 Index = 0;
	InFileName.FindLastChar(L'\\', Index);

	const int32 Length = InFileName.Len() - 1;
	const FString FileName = InFileName.Right(Length - Index);

	UE_LOG(Odyssey, Error, L"%s, %s, %d", *FileName, *InFuncName, InLineNumber);
}

void CDebug::Screen(const int32 InValue, const FColor InColor, const float InDuration, const int32 InKey)
{
	#if WITH_EDITOR
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::FromInt(InValue));
	}
	#endif
}

void CDebug::Screen(const float InValue, const FColor InColor, const float InDuration, const int32 InKey)
{
	#if WITH_EDITOR
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
	}
	#endif
}

void CDebug::Screen(const FString& InValue, const FColor InColor, const float InDuration, const int32 InKey)
{
	#if WITH_EDITOR
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue);
	}
	#endif
}

void CDebug::Screen(const FVector& InValue, const FColor InColor, const float InDuration, const int32 InKey)
{
	#if WITH_EDITOR
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
	}
	#endif
}

void CDebug::Screen(const FRotator& InValue, const FColor InColor, const float InDuration, const int32 InKey)
{
	#if WITH_EDITOR
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
	}
	#endif
}

void CDebug::Screen(const UObject* InValue, const FColor InColor, const float InDuration, const int32 InKey)
{
	#if WITH_EDITOR
	{
		FString Message;

		if (InValue)
			Message.Append(InValue->GetName());

		Message.Append(InValue ? " isn't Null" : " is Null");

		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, Message);
	}
	#endif
}

void CDebug::Screen(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber, const FColor InColor, const float InDuration, const int32 InKey)
{
	#if WITH_EDITOR
	{
		// C:\\Example\\Example.cpp

		int32 Index = 0;
		InFileName.FindLastChar(L'\\', Index);

		const int32 Length = InFileName.Len() - 1;
		const FString FileName = InFileName.Right(Length - Index);

		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::Printf(L"%s, %s, %d", *FileName, *InFuncName, InLineNumber));
	}
	#endif
}
