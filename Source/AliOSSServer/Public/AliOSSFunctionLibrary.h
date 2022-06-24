// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <OssClient.h>
#include <Types.h>

#include "CoreMinimal.h"
#include "AliOSSDataTypes.h"

#include "AliOSSFunctionLibrary.generated.h"

/**
 * @JackMaDrinkCoffee
 * email:596770421@qq.com
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

	//删除Bucket
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Bucket")
	static bool DeleteBudget(const FOSSAccountInfo& AccountInfo, const FString& BucketName);

	//列举Bucket
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Bucket")
	static TArray<FString> ListBucket(const FOSSAccountInfo& AccountInfo);

	//Bucket是否存在
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Bucket")
	static bool DoesBucketExist(const FOSSAccountInfo& AccountInfo, const FString& BucketName);


	/*
	 * upload files functions !
	 * 
	 */

	//上传一个文件
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Upload")
	static bool OssUploadAFile(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& FilePath, const FString& UploadPath);

	//内存上传一串数据
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Upload")
	static bool OssUploadObjectDataFromMemory(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& FilePath, const FString& UploadPath);

	//追加上传
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Upload")
	static bool OssAppendUploadDataFromMemory(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& UploadPath);

	//进度条上传
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Upload")
	static bool OssUploadWithProgress(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& ObjectName);


	
	
	/*
	 * download files
	 * 下载文件 相关
	 */

	//下载文件到本地
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|DownLoad")
	static bool OssDownLoadAFile(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& ObjectName, const FString& SaveFileToPath);

	//
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|DownLoad")
	static bool OssDownLoadAFileToMemory(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& ObjectName);
	
	//进度条下载
	//Download with process
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Upload")
	static bool OssDownLoadWithProcess(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& ObjectName);

	/*
	 * 管理文件：
	 * File Management
	 * 基础操作：
	 * 1.列举文件
	 * 2.拷贝文件
	 * 3.删除文件
	 * 4.文件是否存在
	 * 
	 */

	//列举文件
	//list files as 
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|FileManage")
	static TArray<FOssFileInfo> OssListFilesDefaultOrder(const FOSSAccountInfo& AccountInfo, const FString& BucketName);

	//列举指定个数的文件
	//list dynamic numbers of files 
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|VersionControl")
	static bool OssListBucketNumFile(const FOSSAccountInfo& AccountInfo, const FString& BucketName,const int32& NumTolist);
	
	
	/*
	 * 版本控制：
	 * 版本控制在每次上传或者下载的时候返回的结构体中自动会返回对应的版本号，当然你也可以单独通过SDK访问该文件的版本。
	 * 但是你需要提前设置Bucket具备版本控制功能；
	 * 
	 * VersionControl：
	 * As long as you version buckt, files belonging to that bucket are automatically versioned.
	 * You can get the file version by the upload or download callback or a http request especially for file version.
	 */

	//设置Bucket的版本控制开关
	//Set the Bucket version control state
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|VersionControl")
	static bool OssSetBucketVersioning(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const bool& bIsEnable);

	//获取Bucket版本控制状态信息
	//Get Bucket version control info 
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|VersionControl")
	static bool OssGetBucketVersion(const FOSSAccountInfo& AccountInfo, const FString& BucketName);

	//列举Bucket中所有Object的版本信息
	//List All Bucket files version info;
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|VersionControl")
	static bool OssListBucketAllFileVersion(const FOSSAccountInfo& AccountInfo, const FString& BucketName);



	

	
	
	/*
	 * Utilities function
	 * 
	 */
	UFUNCTION(BlueprintCallable, Category="AliOSSServer|Print")
	static void AlibabaOutComePrintOut(const FString& FailedTitle, const FString& Code, const FString& Message, const FString& RequestId);
	
	static void AlibabaPrintOut(const FString& FailedTitle);

	template<typename T>
	static void AlibabaOutComePrintOut(const FString& FailedTitle,const T& OutCome);
	
	static AlibabaCloud::OSS::OssClient GetDefaultOssClient(const FOSSAccountInfo& AccountInfo);

	static std::string ToStdString(const FString& InStr);
};


