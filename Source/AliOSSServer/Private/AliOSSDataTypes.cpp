// Fill out your copyright notice in the Description page of Project Settings.


#include "AliOSSDataTypes.h"

DEFINE_LOG_CATEGORY(LogOSSServer);

FOSSAccountInfo::FOSSAccountInfo()
{
}

FOSSAccountInfo::FOSSAccountInfo(const std::string& InAccessKeyId, const std::string& InAccessKeySecret, const std::string& InEndpoint, const std::string& InBucketName)
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

FOssOwner::FOssOwner()
{
}

FOssOwner::FOssOwner(const std::string& InId, const std::string& InName)
{
	Id = InId.c_str();
	Name = InName.c_str();
}

FOssOwner::FOssOwner(const FString& InId, const FString& InName)
{
	Id = InId;
	Name = InName;
}

FOssOwner::FOssOwner(const AlibabaCloud::OSS::Owner& InOwner)
{
	FOssOwner(FString(InOwner.Id().c_str()), FString(InOwner.DisplayName().c_str()));
}

FOssFileInfo::FOssFileInfo()
{
}

FOssFileInfo::FOssFileInfo(const std::string& InName, const int64_t& InSize, const std::string& InLastModified, const std::string& InStorageClass, const std::string& InType, const AlibabaCloud::OSS::Owner& InOwner)
{
	Name = InName.c_str();
	Size = InSize;
	LastModified = InLastModified.c_str();
	StorageClass = InStorageClass.c_str();
	Type = InType.c_str();
	Owner = FOssOwner(InOwner);
}

FOssFileInfo::FOssFileInfo(const FString& InName, const int64& InSize, const FString& InLastModified, const FString& InStorageClass, const FString& InType, const AlibabaCloud::OSS::Owner& InOwner)
{
	Name = InName;
	Size = InSize;
	LastModified = InLastModified;
	StorageClass = InStorageClass;
	Type = InType;
	Owner = FOssOwner(InOwner);
}

FOssObjectSummary::FOssObjectSummary(): Size(0)
{
}

FOssObjectSummary::FOssObjectSummary(const AlibabaCloud::OSS::ObjectSummary& ObjectSummary)
{
	Key=ObjectSummary.Key().c_str();
	ETag=ObjectSummary.ETag().c_str();
	Size=ObjectSummary.Size();
	LastModified=ObjectSummary.LastModified().c_str();
	StorageClass=ObjectSummary.StorageClass().c_str();
	Type=ObjectSummary.Type().c_str();
	Owner=ObjectSummary.Owner();
}
