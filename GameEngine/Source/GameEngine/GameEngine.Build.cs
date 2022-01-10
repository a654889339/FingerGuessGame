// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class GameEngine : ModuleRules
{
    private string ThirdPartyPath
    {
        get
        {
//#if (UE_BUILD_DEBUG) || (UE_BUILD_DEVELOPMENT) || (UE_GAME)
            return Path.Combine(Path.Combine(ModuleDirectory, "../../ThirdParty/lib/Debug_X64"));
//#else
//            return Path.Combine(Path.Combine(ModuleDirectory, "../../ThirdParty/lib/Release_X64"));
//#endif
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
//#if (UE_BUILD_DEBUG) || (UE_BUILD_DEVELOPMENT) || (UE_GAME)
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "ClientX64D.lib"));
//#else
//        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "ClientX64.lib"));
//#endif

    }
}
