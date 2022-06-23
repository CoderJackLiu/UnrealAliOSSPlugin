// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AliOSSDataTypes.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LogOSSServer, Log, All);

USTRUCT(BlueprintType, Category = "OSS Runtime")
/** The name, size, shape, and type of the tensor */
struct FOSSAccountInfo
{
	GENERATED_BODY()

public:
	/** Default constructor */
	FOSSAccountInfo();

	/** Construct from standard information of onnx runtime session */
	FOSSAccountInfo(const std::string& InAccessKeyId, const std::string& InAccessKeySecret, const std::string& InEndpoint, const std::string& InBucketName);

	/** Construct from specified parameters */
	FOSSAccountInfo(const FString& InAccessKeyId, const FString& InAccessKeySecret, const FString& InEndpoint, const FString& InBucketName);

	/** The AccessKeyId of the AccountInfo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	FString AccessKeyId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	FString AccessKeySecret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	FString Endpoint;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	// FString BucketName;
	
	std::string GetAccessId() const {return TCHAR_TO_ANSI(*AccessKeyId);}
	std::string GetAccessKeySecret() const {return TCHAR_TO_ANSI(*AccessKeyId);}
	std::string GetEndpoint() const {return TCHAR_TO_ANSI(*AccessKeyId);}
	
};

USTRUCT(BlueprintType, Category = "OSS DataType")
/** The name, size, shape, and type of the tensor */
struct FOssFileInfo
{
	GENERATED_BODY()

public:
	/** Default constructor */
	FOssFileInfo();

	/** Construct from standard information of onnx runtime session */
	FOssFileInfo(const std::string& InName, const int64_t& InSize, const std::string& InLastModified, const std::string& InStorageClass, const std::string& InType,
		const std::string& InOwner);

	/** Construct from specified parameters */
	FOssFileInfo(const FString& InName, const int64& InSize, const FString& InLastModified, const FString& InStorageClass, const FString& InType, const FString& InOwner);

	
	/** The AccessKeyId of the AccountInfo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	int64 Size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	FString LastModified;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	FString StorageClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	FString Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ONNX Runtime")
	FString Owner;

	
	
};


UCLASS()
class ALIOSSSERVER_API UAliOSSDataTypes : public UObject
{
	GENERATED_BODY()

	
};
