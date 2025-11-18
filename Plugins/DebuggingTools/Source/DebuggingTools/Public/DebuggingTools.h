#pragma once

#include "Modules/ModuleManager.h"

class FDebuggingToolsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
