// Fill out your copyright notice in the Description page of Project Settings.


#include "AliOSSDataTypes.h"

DEFINE_LOG_CATEGORY(LogOSSServer);

FOSSAccountInfo::FOSSAccountInfo()
{
}

FOSSAccountInfo::FOSSAccountInfo(const std::string& InAccessKeyId, const std::string& InAccessKeySecret, const std::string& InEndpoint,
                                 const std::string& InBucketName)
{
	AccessKeyId = InAccessKeyId.c_str();
	AccessKeySecret = InAccessKeySecret.c_str();
	Endpoint = InEndpoint.c_str();
	// BucketName = InBucketName.c_str();
}

FOSSAccountInfo::FOSSAccountInfo(const FString& InAccessKeyId, const FString& InAccessKeySecret, const FString& InEndpoint, const FString& InBucketName)
{
	AccessKeyId = InAccessKeyId;
	AccessKeySecret = InAccessKeySecret;
	Endpoint = InEndpoint;
	// BucketName = InBucketName;
}
