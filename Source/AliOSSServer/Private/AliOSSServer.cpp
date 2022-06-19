// Copyright Epic Games, Inc. All Rights Reserved.

#include "AliOSSServer.h"

#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FAliOSSServerModule"

DEFINE_LOG_CATEGORY(LogOSSServer);

class FAliOSSServerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		libcurl = LoadDll(TEXT("libcurl.dll "));
		libeay32 = LoadDll(TEXT("libeay32.dll"));
		ssleay32 = LoadDll(TEXT("ssleay32.dll"));
		zlibwapi = LoadDll(TEXT("zlibwapi.dll"));
	}

	virtual void ShutdownModule() override
	{
		FreeDll(libcurl);
		FreeDll(libeay32);
		FreeDll(ssleay32);
		FreeDll(zlibwapi);
	}

private:
	void* LoadDll(const TCHAR* InDllName)
	{
		void* DllHandle = nullptr;

		// determine directory paths
		FString DllPath = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("AliOSSServer"))->GetBaseDir(),TEXT("/Source/ThirdParty/lib/x64"));
		FPlatformProcess::PushDllDirectory(*DllPath);
		DllPath = FPaths::Combine(DllPath, InDllName);

		if (!FPaths::FileExists(DllPath))
		{
			UE_LOG(LogOSSServer, Error, TEXT("Failed to find the binary folder for %s. Plug-in will not be functional."), InDllName);
			return nullptr;
		}

		DllHandle = FPlatformProcess::GetDllHandle(*DllPath);
		if (!DllHandle)
		{
			UE_LOG(LogOSSServer, Error, TEXT("Failed to load required library %s. Plug-in will not be functional."), *DllPath);
		}

		return DllHandle;
	}

	void FreeDll(void* OutHandle)
	{
		if (OutHandle)
		{
			FPlatformProcess::FreeDllHandle(OutHandle);
			OutHandle = nullptr;
		}
	}
	virtual bool SupportsDynamicReloading() override
	{
		return false;
	}
	
	void* libcurl = nullptr;
	void* libeay32 = nullptr;
	void* ssleay32 = nullptr;
	void* zlibwapi = nullptr;
};
#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAliOSSServerModule, AliOSSServer)
