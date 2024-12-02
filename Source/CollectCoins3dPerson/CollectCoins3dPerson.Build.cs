// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CollectCoins3dPerson : ModuleRules
{
	public CollectCoins3dPerson(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "UMG", "NavigationSystem"});
	}
}
