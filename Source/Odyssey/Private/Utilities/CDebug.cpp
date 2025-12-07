#include "Utilities/CDebug.h"

DEFINE_LOG_CATEGORY_STATIC(Odyssey, Display, All)

void CDebug::Log(const int32 InValue)
{
    UE_LOG(Odyssey, Warning, L"%d", InValue);
}

void CDebug::Log(const float InValue)
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
    FString Message;

    if (InValue)
       Message.Append(InValue->GetName());

    Message.Append(InValue ? "Not Null" : "Null");

    UE_LOG(Odyssey, Display, L"%s", *Message);
}

void CDebug::Log(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber)
{
    int32 Index = 0;

    InFileName.FindLastChar(L'\\', Index);

    const int32 Length = InFileName.Len() - 1;

    const FString FileName = InFileName.Right(Length - Index);

    UE_LOG(Odyssey, Display, L"%s, %s, %d", *FileName, *InFuncName, InLineNumber);
}

void CDebug::Screen(const int32 InValue, const int32 InKey, const float InDuration, const FColor InColor)
{
#if WITH_EDITOR
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::FromInt(InValue));
#endif
}

void CDebug::Screen(const float InValue, const int32 InKey, const float InDuration, const FColor InColor)
{
#if WITH_EDITOR
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
#endif
}

void CDebug::Screen(const FString& InValue, const int32 InKey, const float InDuration, const FColor InColor)
{
#if WITH_EDITOR
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue);
#endif
}

void CDebug::Screen(const FVector& InValue, const int32 InKey, const float InDuration, const FColor InColor)
{
#if WITH_EDITOR
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
#endif
}

void CDebug::Screen(const FRotator& InValue, const int32 InKey, const float InDuration, const FColor InColor)
{
#if WITH_EDITOR
    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
#endif
}

void CDebug::Screen(const UObject* InValue, const int32 InKey, const float InDuration, const FColor InColor)
{
#if WITH_EDITOR
    FString Message;

    if (InValue)
       Message.Append(InValue->GetName());

    Message.Append(InValue ? "Not Null" : "Null");

    GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, Message);
#endif
}

void CDebug::Screen(const FString& InFileName, const FString& InFuncName, const int32 InLineNumber)
{
#if WITH_EDITOR
    int32 Index = 0;

    InFileName.FindLastChar(L'\\', Index);

    const int32 Length = InFileName.Len() - 1;

    const FString FileName = InFileName.Right(Length - Index);

    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::Printf(L"%s, %s, %d", *FileName, *InFuncName, InLineNumber));
#endif
}