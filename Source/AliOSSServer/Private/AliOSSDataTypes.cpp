// Fill out your copyright notice in the Description page of Project Settings.


#include "AliOSSDataTypes.h"

DEFINE_LOG_CATEGORY(LogOSSServer);

FOSSAccountInfo::FOSSAccountInfo()
{
}

FOSSAccountInfo::FOSSAccountInfo(const std::string& InAccessKeyId, const std::string& InAccessKeySecret, const std::string& InEndpoint,const std::string& InBucketName)
{
	AccessKeyId = InAccessKeyId.c_str();
	AccessKeySecret = InAccessKeySecret.c_str();
	Endpoint = InEndpoint.c_str();
}

FOSSAccountInfo::FOSSAccountInfo(const FString& InAccessKeyId, const FString& InAccessKeySecret, const FString& InEndpoint, const FString& InBucketName)
{
	AccessKeyId = InAccessKeyId;
	AccessKeySecret = InAccessKeySecret;
	Endpoint = InEndpoint;
}

FOssFileInfo::FOssFileInfo()
{
}

FOssFileInfo::FOssFileInfo(const std::string& InName, const int64_t& InSize, const std::string& InLastModified, const std::string& InStorageClass,
                           const std::string& InType, const std::string& InOwner)
{
	Name=InName.c_str();
	Size=InSize;
	LastModified=InLastModified.c_str();
	StorageClass=InStorageClass.c_str();
	Type=InType.c_str();
	Owner=InOwner.c_str();
}

FOssFileInfo::FOssFileInfo(const FString& InName, const int64& InSize, const FString& InLastModified, const FString& InStorageClass, const FString& InType,
	const FString& InOwner)
{
	Name=InName;
	Size=InSize;
	LastModified=InLastModified;
	StorageClass=InStorageClass;
	Type=InType;
	Owner=InOwner;
}
