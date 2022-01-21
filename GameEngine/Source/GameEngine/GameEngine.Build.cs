// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class GameEngine : ModuleRules
{
    public GameEngine(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
    
        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine",
            "InputCore",
            "Slate",
            "SlateCore",
        });
        
        RuntimeDependencies.Add(Path.Combine("/ThirdParty/Win64/ClientX64D.dll"));
    }
}
