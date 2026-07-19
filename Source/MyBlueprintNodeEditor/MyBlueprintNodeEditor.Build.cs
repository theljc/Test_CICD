using UnrealBuildTool;

public class MyBlueprintNodeEditor : ModuleRules
{
    public MyBlueprintNodeEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(new string[] { 
                "UnrealEd",
                "KismetCompiler",
                
            });
        }
        
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
                "UnrealPCGExamples",
            }
        );
    }
}