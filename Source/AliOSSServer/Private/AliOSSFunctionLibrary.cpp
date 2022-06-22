// Fill out your copyright notice in the Description page of Project Settings.

#include "AliOSSFunctionLibrary.h"

#include <fstream>
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

bool UAliOSSFunctionLibrary::DoesBucketExist(const FOSSAccountInfo& AccountInfo, const FString& BucketName)
{
	/* 初始化网络等资源 */
	InitializeSdk();

	const OssClient Client = GetDefaultOssClient(AccountInfo);
	/* 判断存储空间是否存在 */
	if (Client.DoesBucketExist(TCHAR_TO_ANSI(*BucketName)))
	{
		std::cout << " The Bucket exists" << std::endl;
	}
	else
	{
		std::cout << "The Bucket does not exist" << std::endl;
	}

	/* 释放网络等资源 */
	ShutdownSdk();
	return false;
}

bool UAliOSSFunctionLibrary::OssUploadAFile(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& FilePath, const FString& UploadPath)
{
	/* 初始化网络等资源。*/
	InitializeSdk();
	/* 初始化OSS账号信息。*/
	const OssClient Client = GetDefaultOssClient(AccountInfo);

	/* 填写本地文件完整路径，例如D:\\localpath\\examplefile.txt，其中localpath为本地文件examplefile.txt所在本地路径。*/
	// std::shared_ptr<std::iostream> content = std::make_shared<std::fstream>("D:\\localpath\\examplefile.txt", std::ios::in | std::ios::binary);
	std::shared_ptr<std::iostream> content = std::make_shared<std::fstream>(TCHAR_TO_ANSI(*FilePath), std::ios::in | std::ios::binary);
	PutObjectRequest request(TCHAR_TO_ANSI(*BucketName), TCHAR_TO_ANSI(*UploadPath),  content);

	/*（可选）请参见如下示例设置访问权限ACL为私有（private）以及存储类型为标准存储（Standard）。*/
	//request.MetaData().addHeader("x-oss-object-acl", "private");
	//request.MetaData().addHeader("x-oss-storage-class", "Standard");

	auto outcome = Client.PutObject(request);

	if (!outcome.isSuccess())
	{
		/* 异常处理。*/
		AlibabaPrintOut("PutObject fail", outcome.error().Code().c_str(), outcome.error().Code().c_str(), outcome.error().Code().c_str());
		ShutdownSdk();
		return false;
	}
	/* 释放网络等资源。*/
	ShutdownSdk();
	return false;
}

bool UAliOSSFunctionLibrary::OssUploadObjectDataFromMemory(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& FilePath, const FString& UploadPath)
{
	/* 初始化网络等资源。*/
	InitializeSdk();
	OssClient client= GetDefaultOssClient(AccountInfo);
	
	//todo liu 
	std::shared_ptr<std::iostream> Content = std::make_shared<std::stringstream>();
	*Content << "Thank you for using Alibaba Cloud Object Storage Service!";
	PutObjectRequest request(TCHAR_TO_ANSI(*BucketName), TCHAR_TO_ANSI(*UploadPath), Content);

	/*（可选）请参见如下示例设置访问权限ACL为私有（private）以及存储类型为标准存储（Standard）。*/
	//request.MetaData().addHeader("x-oss-object-acl", "private");
	//request.MetaData().addHeader("x-oss-storage-class", "Standard");

	auto outcome = client.PutObject(request);

	if (!outcome.isSuccess()) {
		/* 异常处理。*/
		AlibabaPrintOut("PutObject fail", outcome.error().Code().c_str(), outcome.error().Code().c_str(), outcome.error().Code().c_str());
		ShutdownSdk();
		return false;
	}

	/* 释放网络等资源。*/
	ShutdownSdk();
	return true;
}

bool UAliOSSFunctionLibrary::OssAppendUploadDataFromMemory(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& FilePath,
	const FString& UploadPath)
{
	 /* 初始化OSS账号信息。*/

    /* 填写Object完整路径，完整路径中不能包含Bucket名称，例如exampledir/exampleobject.txt。*/
    std::string ObjectName = "exampledir/exampleobject.txt";

    /* 初始化网络等资源。*/
    InitializeSdk();

    ClientConfiguration conf;
	OssClient client= GetDefaultOssClient(AccountInfo);

    auto meta = ObjectMetaData();
    meta.setContentType("text/plain");

    /* 第一次追加的位置是0，返回值为下一次追加的位置。后续追加的位置是追加前文件的长度。*/
    std::shared_ptr<std::iostream> content1 = std::make_shared<std::stringstream>();
    *content1 <<"Thank you for using Aliyun Object Storage Service!";
    AppendObjectRequest request(TCHAR_TO_ANSI(*BucketName),TCHAR_TO_ANSI(*UploadPath),  content1, meta);
	// PutObjectRequest request(TCHAR_TO_ANSI(*BucketName), TCHAR_TO_ANSI(*UploadPath), Content);

    request.setPosition(0L);

    /* 第一次追加文件。*/
    auto result = client.AppendObject(request);

    if (!result.isSuccess()) {
        /* 异常处理。*/
    	AlibabaPrintOut("AppendObject fail", result.error().Code().c_str(), result.error().Code().c_str(), result.error().Code().c_str());
        ShutdownSdk();
        return false;
    }

    std::shared_ptr<std::iostream> content2 = std::make_shared<std::stringstream>();
    *content2 <<"Thank you for using Aliyun Object Storage Service!";
    auto position = result.result().Length();
    AppendObjectRequest appendObjectRequest(TCHAR_TO_ANSI(*BucketName), ObjectName, content2);
    appendObjectRequest.setPosition(position);

    /* 第二次追加文件。*/
    auto outcome = client.AppendObject(appendObjectRequest);

    if (!outcome.isSuccess()) {
        /* 异常处理。*/
    	AlibabaPrintOut("AppendObject fail", outcome.error().Code().c_str(), outcome.error().Code().c_str(), outcome.error().Code().c_str());
        ShutdownSdk();
        return false;
    }

    /* 释放网络等资源。*/
    ShutdownSdk();
    return true;
}


/*
 * AlibabaOSS utilities!
 */

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
