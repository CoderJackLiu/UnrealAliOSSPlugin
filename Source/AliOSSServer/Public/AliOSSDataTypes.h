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


UCLASS()
class ALIOSSSERVER_API UAliOSSDataTypes : public UObject
{
	GENERATED_BODY()

	
};
