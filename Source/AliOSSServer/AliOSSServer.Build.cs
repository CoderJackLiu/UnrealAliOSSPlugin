// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;


public class AliOSSServer : ModuleRules
{
	private string ThirdPartyPath
	{
		get
		{
			return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/"));
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
		string includePath = Path.Combine(ThirdPartyPath, "include");
		PublicIncludePaths.Add(includePath);
		
		string alibabaPath = Path.Combine(includePath, "alibabacloud");
		PublicIncludePaths.Add(alibabaPath);
		
		string alibabaOssPath = Path.Combine(alibabaPath, "oss");
		PublicIncludePaths.Add(alibabaOssPath);
		
		PublicIncludePaths.Add(Path.Combine(alibabaOssPath, "auth"));		
		PublicIncludePaths.Add(Path.Combine(alibabaOssPath, "client"));		
		PublicIncludePaths.Add(Path.Combine(alibabaOssPath, "encryption"));		
		PublicIncludePaths.Add(Path.Combine(alibabaOssPath, "http"));		
		PublicIncludePaths.Add(Path.Combine(alibabaOssPath, "model"));		
		PublicIncludePaths.Add(Path.Combine(alibabaOssPath, "utils"));	
		
		PublicIncludePaths.Add(Path.Combine(includePath, "curl"));		
		PublicIncludePaths.Add(Path.Combine(includePath, "openssl"));

		string libPath = Path.Combine(ThirdPartyPath, "lib/x64");
		PublicAdditionalLibraries.Add(Path.Combine(libPath, "alibabacloud-oss-cpp-sdk.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(libPath, "libcurl.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(libPath, "libeay32.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(libPath, "ssleay32.lib"));

		// PublicDelayLoadDLLs.Add(Path.Combine(LibPath, "libcurl.dll"));
		// PublicDelayLoadDLLs.Add(Path.Combine(LibPath, "libeay32.dll"));
		// PublicDelayLoadDLLs.Add(Path.Combine(LibPath, "ssleay32.dll"));
		// PublicDelayLoadDLLs.Add(Path.Combine(LibPath, "zlibwapi.dll"));
		
		PublicDelayLoadDLLs.Add("libcurl.dll" );
		PublicDelayLoadDLLs.Add("libeay32.dll");
		PublicDelayLoadDLLs.Add("ssleay32.dll");
		PublicDelayLoadDLLs.Add("zlibwapi.dll");
		
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
				"Projects"
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
