#include "GhostGobbler/Public/GameModes/GGGameModeBase.h"

#include "Controllers/GGPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "GhostGobbler/Public/Characters/GGPlayerPawn.h"

AGGGameModeBase::AGGGameModeBase()
{
	SpawnLocation =FVector(0.0f, 0.0f, 100.f);
}




void AGGGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	TObjectPtr<AGGPlayerController> PC = Cast<AGGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	SpawnPlayerPawn(PC);
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