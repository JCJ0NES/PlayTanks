// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlayTanks : ModuleRules
{
	public PlayTanks(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
