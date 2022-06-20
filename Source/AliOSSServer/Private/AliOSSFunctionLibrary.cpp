// Fill out your copyright notice in the Description page of Project Settings.

#include "AliOSSFunctionLibrary.h"

#include <OssClient.h>

#include "AliOSSDataTypes.h"


using namespace AlibabaCloud::OSS;

bool UAliOSSFunctionLibrary::CreateBudget(const FOSSAccountInfo& AccountInfo, const FString& BucketName)
{
	/* 初始化网络等资源 */
	InitializeSdk();

	OssClient Client = GetDefaultOssClient(AccountInfo);

	/* 指定新创建Bucket的名称、存储类型和ACL */
	CreateBucketRequest request(TCHAR_TO_ANSI(*BucketName), StorageClass::IA, CannedAccessControlList::PublicReadWrite);

	/* 创建Bucket */
	auto outcome = Client.CreateBucket(request);

	if (!outcome.isSuccess())
	{
		/* 异常处理 */
		AlibabaPrintOut("CreateBucket fail", outcome.error().Code().c_str(), outcome.error().Message().c_str(), outcome.error().RequestId().c_str());
		ShutdownSdk();
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Create Succeed!!"));
	/* 释放网络等资源 */
	ShutdownSdk();
	return false;
}

bool UAliOSSFunctionLibrary::CreateBudgetType(const FOSSAccountInfo& AccountInfo, StorageClass Type, CannedAccessControlList ControlList)
{
	return false;
}

bool UAliOSSFunctionLibrary::DeleteBudget(const FOSSAccountInfo& AccountInfo, const FString& BucketName)
{
	/*初始化网络等资源。*/
	InitializeSdk();
	OssClient Client = GetDefaultOssClient(AccountInfo);

	/*删除Bucket。*/
	DeleteBucketRequest request(TCHAR_TO_ANSI(*BucketName));

	auto outcome = Client.DeleteBucket(request);

	//todo 修改为unreal log 弹出窗口，显示返回信息！
	if (!outcome.isSuccess())
	{
		/*异常处理。*/
		AlibabaPrintOut("DeleteBucket fail", outcome.error().Code().c_str(), outcome.error().Message().c_str(), outcome.error().RequestId().c_str());
		ShutdownSdk();
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("delete succeed!"));

	/*释放网络等资源。*/
	ShutdownSdk();
	return true;
}

TArray<FString> UAliOSSFunctionLibrary::ListBucket(const FOSSAccountInfo& AccountInfo)
{
	/*初始化网络等资源。*/
	InitializeSdk();
	OssClient client = GetDefaultOssClient(AccountInfo);
	/*列举当前账号下的所有存储空间。*/
	ListBucketsRequest request;
	auto outcome = client.ListBuckets(request);
	TArray<FString> Infos;
	if (outcome.isSuccess())
	{
		for (auto result : outcome.result().Buckets())
		{
			Infos.Add(result.Name().c_str());
			UE_LOG(LogTemp, Warning, TEXT("BucketName is %s"), *result.Name().c_str());
		}
	}
	else
	{
		/*异常处理。*/
		AlibabaPrintOut("ListBuckets fail", outcome.error().Code().c_str(), outcome.error().Code().c_str(), outcome.error().Code().c_str());
		ShutdownSdk();
		return TArray<FString>();
	}
	/*释放网络等资源。*/
	ShutdownSdk();
	return Infos;
}

bool UAliOSSFunctionLibrary::HasBucket(const FOSSAccountInfo& AccountInfo, const FString& BucketName)
{
	/* 初始化网络等资源 */
	InitializeSdk();

	OssClient Client = GetDefaultOssClient(AccountInfo);
	/* 判断存储空间是否存在 */
	if (Client.DoesBucketExist(TCHAR_TO_ANSI(*BucketName))) {    
		std::cout << " The Bucket exists" << std::endl;
	}
	else {
		std::cout << "The Bucket does not exist" << std::endl;
	}

	/* 释放网络等资源 */
	ShutdownSdk();
	return false;
}

OssClient UAliOSSFunctionLibrary::GetDefaultOssClient(const FOSSAccountInfo& AccountInfo)
{
	const ClientConfiguration Config;
	OssClient Client(AccountInfo.GetEndpoint(), AccountInfo.GetAccessId(), AccountInfo.GetAccessKeySecret(), Config);
	return Client;
}

void UAliOSSFunctionLibrary::AlibabaPrintOut(const FString& FailedTitle, const FString& Code, const FString& Message, const FString& RequestId)
{
	UE_LOG(LogOSSServer, Error, TEXT("%s : code is : %s ;\n Message is %s ;\n RequestId is %s; \n"), *FailedTitle, *Code, *Message, *RequestId);
}
