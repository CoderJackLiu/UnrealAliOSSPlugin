// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;


public class AliOSSServer : ModuleRules
{
	private string ThirdPartyPath
	{
		get
		{
			return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty"));
		}
	}
	public AliOSSServer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/libabacloud/oss"));		
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/libabacloud/oss/auth"));		
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/libabacloud/oss/client"));		
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/libabacloud/oss/encryption"));		
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/libabacloud/oss/http"));		
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/libabacloud/oss/model"));		
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/libabacloud/oss/utils"));	
		
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/curl"));		
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/openssl"));	
		
		PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib/x64/alibabacloud-oss-cpp-sdk.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib/x64/libcurl.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib/x64/libeay32.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib/x64/ssleay32.lib"));
		
		PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "lib/x64/libcurl.dll"));
		PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "lib/x64/libeay32.dll"));
		PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "lib/x64/ssleay32.dll"));
		PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "lib/x64/zlibwapi.dll"));
		
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
