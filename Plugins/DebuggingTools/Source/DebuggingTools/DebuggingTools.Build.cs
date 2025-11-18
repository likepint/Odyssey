using UnrealBuildTool;

public class DebuggingTools : ModuleRules
{
	public DebuggingTools(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.Add("Odyssey");

		PublicDependencyModuleNames.Add("Core");

		PrivateDependencyModuleNames.Add("CoreUObject");
		PrivateDependencyModuleNames.Add("Engine");
		PrivateDependencyModuleNames.Add("Slate");
		PrivateDependencyModuleNames.Add("SlateCore");

		PrivateDependencyModuleNames.Add("GameplayDebugger");
	}
}