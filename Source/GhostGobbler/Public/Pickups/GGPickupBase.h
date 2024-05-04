// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGPickupBase.generated.h"

class USphereComponent;

UCLASS()
class GHOSTGOBBLER_API AGGPickupBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickupBase|Components")
	TObjectPtr<USphereComponent> SphereComp;  //Will use this as root component AND for Overlaps
	
	
public:
	AGGPickupBase();
	virtual void Tick(float DeltaTime) override;



	
protected:
	virtual void BeginPlay() override;

	//virtual void PostInitializeComponents() override; 


	UFUNCTION()   //UFUNCTION() Macro required to use this as a callback function for Dynamic Delegate. Marked as virtual to override in child classes
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
public:

};
