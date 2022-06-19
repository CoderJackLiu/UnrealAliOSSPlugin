// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AliOSSDataTypes.h"
#include "GameFramework/Actor.h"
#include "TestOSSActor.generated.h"

UCLASS()
class ALIOSSSERVER_API ATestOSSActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestOSSActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="OSSServer|Account")
	FOSSAccountInfo AccountInfo;
};
