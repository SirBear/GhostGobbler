#include "GhostGobbler/Public/GameModes/GGGameModeBase.h"

#include "Controllers/GGPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "GhostGobbler/Public/Characters/GGPlayerPawn.h"		// Custom C++ class for the Player Pawn
#include "Cameras/GGCameraPawn.h"								// Custom C++ class for the Camera Pawn

AGGGameModeBase::AGGGameModeBase()
{
	SpawnLocation =FVector(0.0f, 0.0f, 100.f);
}




void AGGGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	TObjectPtr<AGGPlayerController> PC = Cast<AGGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	SpawnPlayerPawn(PC);  // Spawns the C++ Class (BP Instance) that we specify and pass a reference to the Player Controller
}

void AGGGameModeBase::SpawnPlayerPawn(AGGPlayerController* InPlayerController)
{
	if (InPlayerController == nullptr) return; //Early return if the PlayerController is invalid
	
	TObjectPtr<UWorld> World = GetWorld();
	FActorSpawnParameters SpawnParams;

	if (World)
	{
		TObjectPtr<AGGPlayerPawn> SpawnedPlayerPawn = World -> SpawnActor<AGGPlayerPawn>(PlayerPawnToSpawn, SpawnLocation, FRotator(0.0f), SpawnParams);
		if (SpawnedPlayerPawn)
		{
			InPlayerController->SetPlayerPawn(SpawnedPlayerPawn);
		}
	}
	
	
}

void AGGGameModeBase::SpawnCameraPawn(AGGPlayerController* InPlayerController)
{
	if (InPlayerController == nullptr) return; //Early return if the PlayerController is invalid

	TObjectPtr<UWorld> World = GetWorld();
	FActorSpawnParameters SpawnParams;
	
	if (World)
	{
		TObjectPtr<AGGCameraPawn> SpawnedCameraPawn = World -> SpawnActor<AGGCameraPawn>(CameraPawnToSpawn, SpawnLocation, FRotator(0.0f), SpawnParams);
		if (SpawnedCameraPawn)
		{
			InPlayerController -> SetCameraPawn(SpawnedCameraPawn);
		}
	}
}