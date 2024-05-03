#include "GhostGobbler/Public/Characters/GGPlayerPawn.h"

#include "Components/GGPawnMovementComponent.h"             //Inherits from UPawnMovementComponent

AGGPlayerPawn::AGGPlayerPawn()
{

	PrimaryActorTick.bCanEverTick = true;

	BaseStaticMesh01 = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComp01");
	BaseStaticMesh02 = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComp02");

	SetRootComponent(BaseStaticMesh01); //Needed for root component to get proper movement
	BaseStaticMesh02 -> SetupAttachment(BaseStaticMesh01);

	
	PawnMovementComp = CreateDefaultSubobject<UGGPawnMovementComponent>("FloatingPawnMovementComp");
	// Set UpdatedComponent on the PawmMovementComp to the root component
	// .... (component we want to move when we add Movement Input to the MovementComponent)
	PawnMovementComp -> UpdatedComponent = GetRootComponent();

	
}


void AGGPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGGPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UPawnMovementComponent* AGGPlayerPawn::GetMovementComponent() const
{
	if (PawnMovementComp) return PawnMovementComp; //Only return if valid
	return nullptr; //else...return nullptr
}
