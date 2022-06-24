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
		AlibabaOutComePrintOut("CreateBucket fail", outcome.error().Code().c_str(), outcome.error().Message().c_str(), outcome.error().RequestId().c_str());
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
		AlibabaOutComePrintOut("DeleteBucket fail", outcome.error().Code().c_str(), outcome.error().Message().c_str(), outcome.error().RequestId().c_str());
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
		AlibabaOutComePrintOut("ListBuckets fail", outcome.error().Code().c_str(), outcome.error().Code().c_str(), outcome.error().Code().c_str());
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
		UE_LOG(LogOSSServer, Warning, TEXT("The Bucket exists"));
	}
	else
	{
		UE_LOG(LogOSSServer, Warning, TEXT("The Bucket does not exist"));
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
	PutObjectRequest request(TCHAR_TO_ANSI(*BucketName), TCHAR_TO_ANSI(*UploadPath), content);

	/*（可选）请参见如下示例设置访问权限ACL为私有（private）以及存储类型为标准存储（Standard）。*/
	//request.MetaData().addHeader("x-oss-object-acl", "private");
	//request.MetaData().addHeader("x-oss-storage-class", "Standard");

	auto outcome = Client.PutObject(request);

	if (!outcome.isSuccess())
	{
		/* 异常处理。*/
		AlibabaOutComePrintOut("PutObject fail", outcome.error().Code().c_str(), outcome.error().Code().c_str(), outcome.error().Code().c_str());
		ShutdownSdk();
		return false;
	}
	/* 释放网络等资源。*/
	ShutdownSdk();
	return false;
}

bool UAliOSSFunctionLibrary::OssUploadObjectDataFromMemory(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& FilePath,
                                                           const FString& UploadPath)
{
	/* 初始化网络等资源。*/
	InitializeSdk();
	OssClient client = GetDefaultOssClient(AccountInfo);

	//todo liu 
	std::shared_ptr<std::iostream> Content = std::make_shared<std::stringstream>();
	*Content << "Thank you for using Alibaba Cloud Object Storage Service!";
	PutObjectRequest request(TCHAR_TO_ANSI(*BucketName), TCHAR_TO_ANSI(*UploadPath), Content);

	/*（可选）请参见如下示例设置访问权限ACL为私有（private）以及存储类型为标准存储（Standard）。*/
	//request.MetaData().addHeader("x-oss-object-acl", "private");
	//request.MetaData().addHeader("x-oss-storage-class", "Standard");

	auto outcome = client.PutObject(request);

	if (!outcome.isSuccess())
	{
		/* 异常处理。*/
		AlibabaOutComePrintOut("PutObject fail", outcome.error().Code().c_str(), outcome.error().Code().c_str(), outcome.error().Code().c_str());
		ShutdownSdk();
		return false;
	}

	/* 释放网络等资源。*/
	ShutdownSdk();
	return true;
}

bool UAliOSSFunctionLibrary::OssAppendUploadDataFromMemory(const FOSSAccountInfo& AccountInfo, const FString& BucketName,
                                                           const FString& UploadPath)
{
	/* 初始化OSS账号信息。*/

	/* 填写Object完整路径，完整路径中不能包含Bucket名称，例如exampledir/exampleobject.txt。*/
	std::string ObjectName = "exampledir/exampleobject.txt";

	/* 初始化网络等资源。*/
	InitializeSdk();

	OssClient client = GetDefaultOssClient(AccountInfo);

	auto meta = ObjectMetaData();
	meta.setContentType("text/plain");

	/* 第一次追加的位置是0，返回值为下一次追加的位置。后续追加的位置是追加前文件的长度。*/
	std::shared_ptr<std::iostream> content1 = std::make_shared<std::stringstream>();
	*content1 << "Thank you for using Aliyun Object Storage Service!";
	AppendObjectRequest request(TCHAR_TO_ANSI(*BucketName),TCHAR_TO_ANSI(*UploadPath), content1, meta);
	// PutObjectRequest request(TCHAR_TO_ANSI(*BucketName), TCHAR_TO_ANSI(*UploadPath), Content);

	request.setPosition(0L);

	/* 第一次追加文件。*/
	auto result = client.AppendObject(request);

	if (!result.isSuccess())
	{
		/* 异常处理。*/
		AlibabaOutComePrintOut("AppendObject fail", result.error().Code().c_str(), result.error().Code().c_str(), result.error().Code().c_str());
		ShutdownSdk();
		return false;
	}

	std::shared_ptr<std::iostream> content2 = std::make_shared<std::stringstream>();
	*content2 << "Thank you for using Aliyun Object Storage Service!";
	auto position = result.result().Length();
	AppendObjectRequest appendObjectRequest(TCHAR_TO_ANSI(*BucketName), ObjectName, content2);
	appendObjectRequest.setPosition(position);

	/* 第二次追加文件。*/
	auto outcome = client.AppendObject(appendObjectRequest);

	if (!outcome.isSuccess())
	{
		/* 异常处理。*/
		AlibabaOutComePrintOut("AppendObject fail", outcome.error().Code().c_str(), outcome.error().Code().c_str(), outcome.error().Code().c_str());
		ShutdownSdk();
		return false;
	}

	/* 释放网络等资源。*/
	ShutdownSdk();
	return true;
}

void UpLoadProgressCallback(size_t increment, int64_t transfered, int64_t total, void* userData)
{
	std::cout << "ProgressCallback[" << userData << "] => " << increment << " ," << transfered << "," << total << std::endl;
	UE_LOG(LogOSSServer, Warning, TEXT("increment : %d ;transfered : %d ;total : %d"), increment, transfered, total);
}

bool UAliOSSFunctionLibrary::OssUploadWithProgress(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& ObjectName)
{
	/* 初始化OSS账号信息 */
	/* 初始化网络等资源 */
	InitializeSdk();
	OssClient client = GetDefaultOssClient(AccountInfo);

	std::shared_ptr<std::iostream> content = std::make_shared<std::fstream>("yourLocalFilename", std::ios::in | std::ios::binary);
	PutObjectRequest request(ToStdString(BucketName), ToStdString(ObjectName), content);

	TransferProgress progressCallback = {UpLoadProgressCallback, nullptr};
	request.setTransferProgress(progressCallback);

	/* 上传文件 */
	auto outcome = client.PutObject(request);

	if (!outcome.isSuccess())
	{
		/* 异常处理 */
		AlibabaOutComePrintOut("PutObject fail", outcome);
		ShutdownSdk();
		return false;
	}

	/* 释放网络等资源 */
	ShutdownSdk();
	return true;
}

bool UAliOSSFunctionLibrary::OssDownLoadAFile(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& ObjectName, const FString& SaveFileToPath)
{
	/* 初始化OSS账号信息。*/
	//std::string ObjectName = "exampledir/exampleobject.txt";
	//std::string FileNametoSave = "D:\\localpath\\examplefile.txt";

	/* 初始化网络等资源。*/
	InitializeSdk();

	OssClient client = GetDefaultOssClient(AccountInfo);

	/* 下载Object到本地文件。*/
	GetObjectRequest request(ToStdString(BucketName), ToStdString(ObjectName));
	request.setResponseStreamFactory([=]()
	{
		return std::make_shared<std::fstream>(ToStdString(SaveFileToPath), std::ios_base::out | std::ios_base::in | std::ios_base::trunc | std::ios_base::binary);
	});

	auto outcome = client.GetObject(request);

	if (outcome.isSuccess())
	{
		std::cout << "GetObjectToFile success" << outcome.result().Metadata().ContentLength() << std::endl;
	}
	else
	{
		/* 异常处理。*/
		AlibabaOutComePrintOut("GetObjectToFile fail", outcome);
		ShutdownSdk();
		return false;
	}

	/* 释放网络等资源。*/
	ShutdownSdk();

	return true;
}

bool UAliOSSFunctionLibrary::OssDownLoadAFileToMemory(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& ObjectName)
{
	/*初始化OSS账号信息。*/
	OssClient client = GetDefaultOssClient(AccountInfo);
	/*初始化网络等资源。*/
	InitializeSdk();
	/*获取文件到本地内存。*/
	GetObjectRequest request(ToStdString(BucketName), ToStdString(ObjectName));
	auto outcome = client.GetObject(request);
	if (outcome.isSuccess())
	{
		//todo log for out succeed！
		std::cout << "getObjectToBuffer" << " success, Content-Length:" << outcome.result().Metadata().ContentLength() << std::endl;

		/*通过read接口读取数据。*/
		auto& stream = outcome.result().Content();
		char buffer[256];
		while (stream->good())
		{
			stream->read(buffer, 256);
			auto count = stream->gcount();
			/*根据实际情况处理数据。*/
		}
	}
	else
	{
		/*异常处理。*/
		AlibabaOutComePrintOut("getObjectToBuffer fail", outcome);
		ShutdownSdk();
		return false;
	}
	/*释放网络等资源。*/
	ShutdownSdk();
	return false;
}

void DownLoadProgressCallback(size_t increment, int64_t transfered, int64_t total, void* userData)
{
	std::cout << "ProgressCallback[" << userData << "] => " << increment << " ," << transfered << "," << total << std::endl;
	UE_LOG(LogOSSServer, Warning, TEXT("increment : %d ;transfered : %d ;total : %d"), increment, transfered, total);
}

bool UAliOSSFunctionLibrary::OssDownLoadWithProcess(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const FString& ObjectName)
{
	/* 初始化网络等资源 */
	InitializeSdk();

	const OssClient Client = GetDefaultOssClient(AccountInfo);

	/* 获取文件 */
	GetObjectRequest request(ToStdString(BucketName), ToStdString(ObjectName));
	TransferProgress ProgressCallback = {DownLoadProgressCallback, nullptr};
	request.setTransferProgress(ProgressCallback);

	auto outcome = Client.GetObject(request);

	if (!outcome.isSuccess())
	{
		/* 异常处理 */
		AlibabaOutComePrintOut("getObject fail", outcome);
		ShutdownSdk();
		return false;
	}

	/* 释放网络等资源 */
	ShutdownSdk();
	return true;
}

TArray<FOssFileInfo> UAliOSSFunctionLibrary::OssListFilesDefaultOrder(const FOSSAccountInfo& AccountInfo, const FString& BucketName)
{
	TArray<FOssFileInfo> FileInfos;

	InitializeSdk();

	const OssClient Client = GetDefaultOssClient(AccountInfo);

	/* 列举文件。*/
	const ListObjectsRequest Request(ToStdString(BucketName));
	auto outcome = Client.ListObjects(Request);

	if (!outcome.isSuccess())
	{
		/* 异常处理。*/
		AlibabaOutComePrintOut("ListObjects fail", outcome);
		ShutdownSdk();
	}
	else
	{
		for (const auto& object : outcome.result().ObjectSummarys())
		{
			UE_LOG(LogOSSServer, Warning, TEXT("object info name: %s ,size : %d ,lastmodify time ：%s"), *object.Key().c_str(), object.Size(),
			       *object.LastModified().c_str());
			FileInfos.Add(FOssFileInfo(object.Key(), object.Size(), object.LastModified(), object.StorageClass(), object.Type(), object.Owner()));
		}
	}
	/* 释放网络等资源。*/
	ShutdownSdk();
	return FileInfos;
}

TArray<FOssObjectSummary> UAliOSSFunctionLibrary::OssListBucketNumFile(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const int32& NumTolist)
{
	TArray<FOssObjectSummary> ObjectSummaries;
	InitializeSdk();

	ClientConfiguration conf;
	const OssClient Client = GetDefaultOssClient(AccountInfo);

	/* 列举文件。*/
	ListObjectsRequest Request(ToStdString(BucketName));
	/* 设置列举文件的最大个数为200。*/
	Request.setMaxKeys(NumTolist);
	auto Outcome = Client.ListObjects(Request);

	if (!Outcome.isSuccess())
	{
		/* 异常处理。*/
		AlibabaOutComePrintOut("ListObjects fail", Outcome.error().Code().c_str(), Outcome.error().Message().c_str(), Outcome.error().RequestId().c_str());
	}
	else
	{
		for (const auto& object : Outcome.result().ObjectSummarys())
		{
			ObjectSummaries.Add(FOssObjectSummary(object));
		}
	}
	/* 释放网络等资源。*/
	ShutdownSdk();
	return ObjectSummaries;
}

bool UAliOSSFunctionLibrary::OssSetBucketVersioning(const FOSSAccountInfo& AccountInfo, const FString& BucketName, const bool& bIsEnable)
{
	InitializeSdk();
	OssClient client = GetDefaultOssClient(AccountInfo);
	/*创建bucket版本配置，状态设置为Enabled或Suspended*/
	SetBucketVersioningRequest Request(ToStdString(BucketName), VersioningStatus::Enabled);
	auto Outcome = client.SetBucketVersioning(Request);
	if (!Outcome.isSuccess())
	{
		/* 异常处理 */
		AlibabaOutComePrintOut("SetBucketVersioning fail", Outcome.error().Code().c_str(), Outcome.error().Message().c_str(), Outcome.error().RequestId().c_str());
		ShutdownSdk();
		return false;
	}
	/*释放网络等资源*/
	ShutdownSdk();
	return true;
}

bool UAliOSSFunctionLibrary::OssGetBucketVersion(const FOSSAccountInfo& AccountInfo, const FString& BucketName, EOssBucketVersionStatus& VersionStatus)
{
	InitializeSdk();
	OssClient client = GetDefaultOssClient(AccountInfo);
	/**/
	SetBucketVersioningRequest Request(ToStdString(BucketName), VersioningStatus::Enabled);
	auto Outcome = client.GetBucketVersioning(GetBucketVersioningRequest(ToStdString(BucketName)));
	if (!Outcome.isSuccess())
	{
		/* 异常处理 */
		AlibabaOutComePrintOut("GetBucketVersioning fail", Outcome.error().Code().c_str(), Outcome.error().Message().c_str(), Outcome.error().RequestId().c_str());
		ShutdownSdk();
		return false;
	}
	VersionStatus = ConvertOssBucketVersionStatus(Outcome.result().Status());
	/*释放网络等资源*/
	ShutdownSdk();
	return true;
}

bool UAliOSSFunctionLibrary::OssListBucketAllFileVersion(const FOSSAccountInfo& AccountInfo, const FString& BucketName)
{
	/* 初始化网络等资源 */
	InitializeSdk();

	ClientConfiguration conf;
	const OssClient Client = GetDefaultOssClient(AccountInfo);

	ListObjectVersionsRequest request(ToStdString(BucketName));
	bool IsTruncated = false;

	do
	{
		auto Outcome = Client.ListObjectVersions(request);

		if (Outcome.isSuccess())
		{
			/*查看列出的object删除标记的各版本信息*/
			for (auto const& marker : Outcome.result().DeleteMarkerSummarys())
			{
				UE_LOG(LogTemp, Warning, TEXT("marker key: %s ,marker versionid:%s"), *marker.Key().c_str(), *marker.VersionId().c_str());
				
			}

			/*查看列出的object各版本信息*/
			for (auto const& obj : Outcome.result().ObjectVersionSummarys())
			{
				UE_LOG(LogTemp, Warning, TEXT("object key: %s ,object versionid:%s"), *obj.Key().c_str(), *obj.VersionId().c_str());
			}
		}
		else
		{
			AlibabaOutComePrintOut("ListObjectVersions fail", Outcome.error().Code().c_str(), Outcome.error().Message().c_str(), Outcome.error().RequestId().c_str());
			break;
		}
		request.setKeyMarker(Outcome.result().NextKeyMarker());
		request.setVersionIdMarker(Outcome.result().NextVersionIdMarker());
		IsTruncated = Outcome.result().IsTruncated();
	}
	while (IsTruncated);
	/* 释放网络等资源 */
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

std::string UAliOSSFunctionLibrary::ToStdString(const FString& InStr)
{
	return TCHAR_TO_ANSI(*InStr);
}

EOssBucketVersionStatus UAliOSSFunctionLibrary::ConvertOssBucketVersionStatus(const AlibabaCloud::OSS::VersioningStatus& VersioningStatus)
{
	EOssBucketVersionStatus status;
	switch (VersioningStatus)
	{
	case VersioningStatus::NotSet:
		status = EOssBucketVersionStatus::NotSet;
		break;
	case VersioningStatus::Enabled:
		status = EOssBucketVersionStatus::Enabled;
		break;
	case VersioningStatus::Suspended:
		status = EOssBucketVersionStatus::Suspended;
		break;
	default:
		status = EOssBucketVersionStatus::NotSet;
	}
	return status;
}

void UAliOSSFunctionLibrary::AlibabaOutComePrintOut(const FString& FailedTitle, const FString& Code, const FString& Message, const FString& RequestId)
{
	UE_LOG(LogOSSServer, Error, TEXT("%s : code is : %s ;\n Message is %s ;\n RequestId is %s; \n"), *FailedTitle, *Code, *Message, *RequestId);
}

void UAliOSSFunctionLibrary::AlibabaPrintOut(const FString& FailedTitle)
{
	UE_LOG(LogOSSServer, Error, TEXT("%s"), *FailedTitle);
}


template <typename T>
void UAliOSSFunctionLibrary::AlibabaOutComePrintOut(const FString& FailedTitle, const T& OutCome)
{
	UE_LOG(LogOSSServer, Error, TEXT("%s : code is : %s ;\n Message is %s ;\n RequestId is %s; \n"), *FailedTitle, *OutCome.error().Code().c_str(),
	       *OutCome.error().Message().c_str(), *OutCome.error().RequestId().c_str());
}
