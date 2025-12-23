#pragma once

#include "CoreMinimal.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "Utilities/CHelpers.h"
#include "Utilities/CDebug.h"

#define CHECK_TRUE(InValue) \
		{ \
			if (InValue == true) \
				return; \
		}

#define CHECK_TRUE_RESULT(InValue, OutValue) \
		{ \
			if (InValue == true) \
				return OutValue; \
		}

#define CHECK_FALSE(InValue) \
		{ \
			if (InValue == false) \
				return; \
		}

#define CHECK_FALSE_RESULT(InValue, OutValue) \
		{ \
			if (InValue == false) \
				return OutValue; \
		}

#define CHECK_NULL(InValue) \
		{ \
			if (InValue == nullptr) \
				return; \
		}

#define CHECK_NULL_RESULT(InValue, OutValue) \
		{ \
			if (InValue == nullptr) \
				return OutValue; \
		}
