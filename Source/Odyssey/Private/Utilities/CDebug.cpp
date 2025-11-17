#include "Utilities/CDebug.h"

DEFINE_LOG_CATEGORY_STATIC(Odyssey, Display, All)

void CDebug::Log(int32 InValue)
{
	UE_LOG(Odyssey, Warning, L"%d", InValue);
}

void CDebug::Log(float InValue)
{
	UE_LOG(Odyssey, Warning, L"%f", InValue);
}

void CDebug::Log(const FString& InValue)
{
	UE_LOG(Odyssey, Warning, L"%s", *InValue);
}

void CDebug::Log(const FVector& InValue)
{
	UE_LOG(Odyssey, Warning, L"%s", *InValue.ToString());
}

void CDebug::Log(const FRotator& InValue)
{
	UE_LOG(Odyssey, Warning, L"%s", *InValue.ToString());
}

void CDebug::Log(const UObject* InValue)
{
	FString message;

	if (InValue)
		message.Append(InValue->GetName());

	message.Append(InValue ? " Not Null" : "Null");

	UE_LOG(Odyssey, Display, L"%s", *message);
}

void CDebug::Log(const FString& InFileName, const FString& InFuncName, int32 InLineNumber)
{
	int32 index = 0;
	
	InFileName.FindLastChar(L'\\', index);

	int32 length = InFileName.Len() - 1;
	
	FString fileName = InFileName.Right(length - index);

	UE_LOG(Odyssey, Display, L"%s, %s, %d", *fileName, *InFuncName, InLineNumber);
}

void CDebug::Screen(int32 InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::FromInt(InValue));
}

void CDebug::Screen(float InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
}

void CDebug::Screen(const FString& InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue);
}

void CDebug::Screen(const FVector& InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
}

void CDebug::Screen(const FRotator& InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
}

void CDebug::Screen(const UObject* InValue, int32 InKey, float InDuration, FColor InColor)
{
	FString message;

	if (InValue)
		message.Append(InValue->GetName());

	message.Append(InValue ? " Not Null" : "Null");

	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, message);
}

void CDebug::Screen(const FString& InFileName, const FString& InFuncName, int32 InLineNumber)
{
	int32 index = 0;
	
	InFileName.FindLastChar(L'\\', index);

	int32 length = InFileName.Len() - 1;
	
	FString fileName = InFileName.Right(length - index);
	
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::Printf(L"%s, %s, %d", *fileName, *InFuncName, InLineNumber));
}
