// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGSpawnCharactersManager.generated.h"

UCLASS()
class GHOSTGOBBLER_API AGGSpawnCharactersManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGGSpawnCharactersManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
