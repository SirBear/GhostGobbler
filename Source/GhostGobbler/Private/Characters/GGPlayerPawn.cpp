#include "GhostGobbler/Public/Characters/GGPlayerPawn.h"

#include "Components/GGPawnMovementComponent.h"             //Inherits from UPawnMovementComponent
#include "Components/SphereComponent.h"

AGGPlayerPawn::AGGPlayerPawn()
{

	PrimaryActorTick.bCanEverTick = true;


	RootComp = CreateDefaultSubobject<USphereComponent>("RootComp");
	SetRootComponent(RootComp);
	
	Mesh_TopMouth = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_TopMouth");
	Mesh_BottomMouth = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_BottomMouth");

	Mesh_TopMouth -> SetupAttachment(RootComp);
	Mesh_BottomMouth -> SetupAttachment(RootComp);

	
	PawnMovementComp = CreateDefaultSubobject<UGGPawnMovementComponent>("FloatingPawnMovementComp");
	// Set UpdatedComponent on the PawmMovementComp to the root component
	// .... (component we want to move when we add Movement Input to the MovementComponent)
	PawnMovementComp -> UpdatedComponent = GetRootComponent();


	bMoveMouth = false;				// Shouldnt be moving to start. Set default to false
	bOpeningJaws = true;			// Start by moving jaws open
	MouthRotationRate= 1.0f;		// How fast should the jaws open and close?
	Delay_StopMovingMouth = 0.7f;	// Stop moving the mouth after x seconds

	
	
}


void AGGPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGGPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveMouth();  //Calling MoveMouth() custom C++ function
}

UPawnMovementComponent* AGGPlayerPawn::GetMovementComponent() const
{
	if (PawnMovementComp) return PawnMovementComp; //Only return if valid
	return nullptr; //else...return nullptr
}


void AGGPlayerPawn::MoveMouth()
{

	
	if (bMoveMouth)
	{
		FRotator Mesh_TopMouth_CurrentRotation = Mesh_TopMouth->GetRelativeRotation();
		FRotator Mesh_BottomMouth_CurrentRotation = Mesh_BottomMouth->GetRelativeRotation();

		//Zero out Pitch and Roll (for both jaws
		Mesh_TopMouth_CurrentRotation.Roll = 0.0f;
		Mesh_TopMouth_CurrentRotation.Pitch = 0.0f;
		Mesh_BottomMouth_CurrentRotation.Roll = 0.0f;
		Mesh_BottomMouth_CurrentRotation.Pitch = 0.0f;
		
		FRotator Mesh_TopMouth_NewRotation;
		FRotator Mesh_BottomMouth_NewRotation;

		if (bOpeningJaws)	//If True: Pacman is currently opening jaws
		{
			Mesh_TopMouth_NewRotation = Mesh_TopMouth_CurrentRotation - FRotator(0.0f, MouthRotationRate, 0.0f );
			Mesh_BottomMouth_NewRotation = Mesh_BottomMouth_CurrentRotation + FRotator(0.0f, MouthRotationRate, 0.0f );
		}
		else				// If hit this case, then currently closing jaws
		{
			Mesh_TopMouth_NewRotation = Mesh_TopMouth_CurrentRotation + FRotator(0.0f, MouthRotationRate, 0.0f );
			Mesh_BottomMouth_NewRotation = Mesh_BottomMouth_CurrentRotation - FRotator(0.0f, MouthRotationRate, 0.0f );
		}

		// Do we need to update the bool
		if (Mesh_TopMouth_CurrentRotation.Yaw > -40.0f && Mesh_TopMouth_NewRotation.Yaw <= -40.0f)
		{
			bOpeningJaws = false;
		}
		else if (Mesh_TopMouth_CurrentRotation.Yaw < 0.0f && Mesh_TopMouth_NewRotation.Yaw >= 0.0f)
		{
			bOpeningJaws = true;
		}
		
		Mesh_TopMouth -> SetRelativeRotation(Mesh_TopMouth_NewRotation);
		Mesh_BottomMouth -> SetRelativeRotation(Mesh_BottomMouth_NewRotation);
	}
		
}



void AGGPlayerPawn::StopMovingMouth()  //Callback function for Timer in 'StartMovingMouth'
{
	bMoveMouth = false; //Set to False to get jaws to stop moving
}
void AGGPlayerPawn::StartMovingMouth()
{
	bMoveMouth = true;
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_MoveMouth)) // if its currently running then clear the timer
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_MoveMouth); //Clear the timer
	}

	GetWorldTimerManager().SetTimer(TimerHandle_MoveMouth, this, &AGGPlayerPawn::StopMovingMouth, Delay_StopMovingMouth);
}
