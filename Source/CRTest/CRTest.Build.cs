// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CRTest : ModuleRules
{
	public CRTest(ReadOnlyTargetRules Target) : base(Target)
	{
        PublicIncludePaths.AddRange(new string[] { "CRTest" });
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
