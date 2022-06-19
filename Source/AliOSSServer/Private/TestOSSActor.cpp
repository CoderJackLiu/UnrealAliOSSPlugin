// Fill out your copyright notice in the Description page of Project Settings.


#include "TestOSSActor.h"
#include <alibabacloud/oss/OssClient.h>

#include "AliOSSDataTypes.h"
#include "AliOSSFunctionLibrary.h"
using namespace AlibabaCloud::OSS;

//https://help.aliyun.com/document_detail/106556.html

// Sets default values
ATestOSSActor::ATestOSSActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestOSSActor::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ATestOSSActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
