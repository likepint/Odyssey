#pragma once

#include "CoreMinimal.h"

class ODYSSEY_API CHelpers
{
public:	
	template<typename T>
	static void GetAsset(TObjectPtr<T>& OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		if (asset.Succeeded())
			OutObject = asset.Object;
	}
	
	template<typename T>
	static void GetClass(TSubclassOf<T>& OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		if (asset.Succeeded())
			OutClass = asset.Class;
	}

	template<typename T>
	static T* LoadSynchronous(const TSoftObjectPtr<T>& InPath)
	{
		if (!InPath.IsNull())
		{
			if (T* asset = InPath.LoadSynchronous())
				return asset;
		}

		return nullptr;
	}
};
