#pragma once

#include "CoreMinimal.h"

class ODYSSEY_API CHelpers
{
public:
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
