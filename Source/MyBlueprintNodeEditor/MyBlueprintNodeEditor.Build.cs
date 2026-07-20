using UnrealBuildTool;

public class MyBlueprintNodeEditor : ModuleRules
{
    public MyBlueprintNodeEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Engine",
                "CoreUObject",
                "Slate",
                "SlateCore",
                "BlueprintGraph",
                "KismetCompiler",
                "UnrealEd",
                "UnrealPCGExamples",
            }
        );
    }
}