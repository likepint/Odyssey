#pragma once

#include "CoreMinimal.h"

class ODYSSEY_API CHelpers
{
public:	
	template<typename T>
	static void GetAsset(T** OutObject, const FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> Asset(*InPath);
		if (Asset.Succeeded())
			*OutObject = Asset.Object;
	}
	
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, const FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> Asset(*InPath);
		if (Asset.Succeeded())
			*OutClass = Asset.Class;
	}
};
