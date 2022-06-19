// Fill out your copyright notice in the Description page of Project Settings.

#include "AliOSSFunctionLibrary.h"

#include <OssClient.h>

#include "AliOSSDataTypes.h"


using namespace AlibabaCloud::OSS;

bool UAliOSSFunctionLibrary::CreateBudget(const FOSSAccountInfo& AccountInfo)
{

	/* 初始化网络等资源 */
	InitializeSdk();

	ClientConfiguration conf;
	OssClient client(TCHAR_TO_ANSI(*AccountInfo.Endpoint), TCHAR_TO_ANSI(*AccountInfo.AccessKeyId), TCHAR_TO_ANSI(*AccountInfo.AccessKeySecret), conf);

	/* 指定新创建Bucket的名称、存储类型和ACL */
	CreateBucketRequest request(TCHAR_TO_ANSI(*AccountInfo.BucketName), StorageClass::IA, CannedAccessControlList::PublicReadWrite);

	/* 创建Bucket */
	auto outcome = client.CreateBucket(request);

	if (!outcome.isSuccess())
	{
		/* 异常处理 */
		//todo liu 转化为UE_LOG！
		std::cout << "CreateBucket fail" <<
			",code:" << outcome.error().Code() <<
			",message:" << outcome.error().Message() <<
			",requestId:" << outcome.error().RequestId() << std::endl;

		ShutdownSdk();
		UE_LOG(LogTemp, Warning, TEXT("Create failed!"));
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

bool UAliOSSFunctionLibrary::DeleteBudget(const FOSSAccountInfo& AccountInfo)
{
	/*初始化网络等资源。*/
	InitializeSdk();
	ClientConfiguration conf;
	// OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);
	OssClient client(TCHAR_TO_ANSI(*AccountInfo.Endpoint), TCHAR_TO_ANSI(*AccountInfo.AccessKeyId), TCHAR_TO_ANSI(*AccountInfo.AccessKeySecret), conf);

	/*删除Bucket。*/
	DeleteBucketRequest request(TCHAR_TO_ANSI(*AccountInfo.BucketName));
   
	auto outcome = client.DeleteBucket(request);

	//todo 修改为unreal log 弹出窗口，显示返回信息！
	if (!outcome.isSuccess()) {
		/*异常处理。*/
		std::cout << "DeleteBucket fail" <<
		",code:" << outcome.error().Code() <<
		",message:" << outcome.error().Message() <<
		",requestId:" << outcome.error().RequestId() << std::endl;
		ShutdownSdk();
		UE_LOG(LogTemp, Warning, TEXT("delete failed!"));

		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("delete succeed!"));

	/*释放网络等资源。*/
	ShutdownSdk();
	return true;
}
