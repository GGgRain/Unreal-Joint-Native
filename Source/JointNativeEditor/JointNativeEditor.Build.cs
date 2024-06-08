//Copyright 2022~2024 DevGrain. All Rights Reserved.

using UnrealBuildTool;

public class JointNativeEditor : ModuleRules
{
	public JointNativeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrecompileForTargets = PrecompileTargetsType.Any;

		//The path for the source files
			PrivateIncludePaths.AddRange(new[]
			{
				"JointNativeEditor",

				"JointNativeEditor/Public",
				"JointNativeEditor/Public/GraphNode",

			});


			PrivateDependencyModuleNames.AddRange(new string[]
			{
				//Core Dependencies.
				
				"Core",
				"CoreUObject",
				"Engine",
				"UnrealEd",
				
				"Joint",
				"JointNative",
				"JointEditor",
				
				//Additional Dependencies.
				
				"AIGraph",
				"PropertyEditor",
				
				"SlateCore",
				"Slate",
				
				"VoltCore",
				"Volt",
				
				"LevelSequence",
			});

			PublicDependencyModuleNames.AddRange(new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"UnrealEd",
				
				"Joint",
				"JointNative",
				"JointEditor",
			});

	}
}