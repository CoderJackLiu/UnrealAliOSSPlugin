// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	
	UFUNCTION(BlueprintCallable, Category="AliOSSServer")
	static bool CreateBudget(const FOSSAccountInfo& AccountInfo);

	//todo liu convert enum types!
	// UFUNCTION(BlueprintPure, Category="AliOSSServer")
	static bool CreateBudgetType(const FOSSAccountInfo& AccountInfo,AlibabaCloud::OSS::StorageClass Type=AlibabaCloud::OSS::IA, AlibabaCloud::OSS::CannedAccessControlList ControlList= AlibabaCloud::OSS::PublicReadWrite);

	UFUNCTION(BlueprintCallable, Category="AliOSSServer")
	static bool DeleteBudget(const FOSSAccountInfo& AccountInfo);
	
};



