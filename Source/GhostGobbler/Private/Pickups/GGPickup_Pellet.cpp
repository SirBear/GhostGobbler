#include "Pickups/GGPickup_Pellet.h"
#include "Components/StaticMeshComponent.h"


AGGPickup_Pellet::AGGPickup_Pellet()
{
	PrimaryActorTick.bCanEverTick = false;


	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh ->SetupAttachment(GetRootComponent()); //Attach to the RootComp
	
	
}

void AGGPickup_Pellet::BeginPlay()
{
	Super::BeginPlay();
}

void AGGPickup_Pellet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGGPickup_Pellet::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult); //No parent functionality yet. Calling it just to be safe in case I forget later
	
	Destroy(); //Destroy this if we overlap with it
}