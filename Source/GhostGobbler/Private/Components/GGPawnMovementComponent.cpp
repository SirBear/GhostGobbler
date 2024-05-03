#include "Components/GGPawnMovementComponent.h"

UGGPawnMovementComponent::UGGPawnMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	PawnBaseMoveSpeed = 300.f;

}

void UGGPawnMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UGGPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//PawnOwner belongs to the MovementComponent Class, check if Pawn has valid Owner
	//UpdatedComponent was set as the RootComponent in the Pawn C++ Constructor
	//ShouldSkipUpdate() will return true if we should skip this on this particular frame
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) return; //Early return if any return true

	//Get and Clear the Vector. Clamps to value of 1.0f, multiplies by DeltaTime, multiply by the Speed we want
	//Clamp the Vector
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime* PawnBaseMoveSpeed; 

	if(!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		//If we bump into something...slide along it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame,1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}

