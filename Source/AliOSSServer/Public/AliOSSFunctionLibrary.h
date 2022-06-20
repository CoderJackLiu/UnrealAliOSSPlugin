// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <OssClient.h>
#include <Types.h>

#include "CoreMinimal.h"

#include "AliOSSFunctionLibrary.generated.h"

/**
 * 
 */


struct FOSSAccountInfo;

UCLASS(meta=(ScriptName="AliOSSFuncLib"))
class ALIOSSSERVER_API UAliOSSFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Bucket")
	static bool CreateBudget(const FOSSAccountInfo& AccountInfo, const FString& BucketName);

	/*
	 * Bucket functions! 
	 */
	//todo liu convert enum types!
	// UFUNCTION(BlueprintPure, Category="AliOSSServer")
	static bool CreateBudgetType(const FOSSAccountInfo& AccountInfo, AlibabaCloud::OSS::StorageClass Type = AlibabaCloud::OSS::IA,
	                             AlibabaCloud::OSS::CannedAccessControlList ControlList = AlibabaCloud::OSS::PublicReadWrite);

	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Bucket")
	static bool DeleteBudget(const FOSSAccountInfo& AccountInfo, const FString& BucketName);

	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Bucket")
	static TArray<FString> ListBucket(const FOSSAccountInfo& AccountInfo);

	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Bucket")
	static bool DoesBucketExist(const FOSSAccountInfo& AccountInfo,const FString& BucketName);


	
	/*
	 * upload files functions !
	 * 
	 */

	//上传一个文件
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Upload")
	static bool OssUploadAFile(const FOSSAccountInfo& AccountInfo,const FString& BucketName,const FString & FilePath, const FString & UploadPath);

	//内存上传一串数据
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Upload")
	static bool OssUploadObjectDataFromMemory(const FOSSAccountInfo& AccountInfo,const FString& BucketName,const FString & FilePath, const FString & UploadPath);

	//追加上传
	// UFUNCTION(BlueprintCallable, Category="AliOSSServer|Upload")
	// static bool OssUploadObjectDataFromMemory(const FOSSAccountInfo& AccountInfo,const FString& BucketName,const FString & FilePath, const FString & UploadPath);

	
	
	
	/*
	 * Utilities function
	 * 
	 */
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Print")
	// static void AlibabaPrintOut(const FString& FailedTitle, const FString& Code = FString(), const FString& Message = FString(), const FString& RequestId = FString());
	static void AlibabaPrintOut(const FString& FailedTitle, const FString& Code, const FString& Message, const FString& RequestId);


	static AlibabaCloud::OSS::OssClient GetDefaultOssClient(const FOSSAccountInfo& AccountInfo);

	
};
