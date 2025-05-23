// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DomesticWarfare : ModuleRules
{
	public DomesticWarfare(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"NinjaGAS"
		});
	}
}
