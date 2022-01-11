// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class GameEngine : ModuleRules
{
    private string ThirdPartyPath
    {
        get
        {
            return Path.Combine(Path.Combine(ModuleDirectory, "../../ThirdParty"));
        }
    }

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

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Include"));
    }
}
