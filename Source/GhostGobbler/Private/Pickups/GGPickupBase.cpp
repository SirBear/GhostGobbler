#include "Pickups/GGPickupBase.h"
#include "GhostGobbler/Public/Characters/GGPlayerPawn.h"

//#include "ParticleHelper.h"
#include "Components/SphereComponent.h"

AGGPickupBase::AGGPickupBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereComp); //Set this as the new root
}

void AGGPickupBase::BeginPlay()
{
	Super::BeginPlay();

	//Binding custom function to this delegate
	SphereComp -> OnComponentBeginOverlap.AddDynamic(this, &AGGPickupBase::OnSphereBeginOverlap);
	
	
}

void AGGPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGGPickupBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// ----- Removing code. Implement in child classes  ---------------------
	/*if(OtherActor) //OtherActor could be the Player. Need to check its valid
	{
		TObjectPtr<AGGPlayerPawn> PlayerPawn = Cast<AGGPlayerPawn>(OtherActor);
		if (PlayerPawn)  //Is this valid?
		{
			
		}
		
	}*/
}