#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GGGameModeBase.generated.h"


class AGGPlayerController;
class AGGPlayerPawn;
class AGGCameraPawn;

UCLASS()
class GHOSTGOBBLER_API AGGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	FVector SpawnLocation;  

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<AGGPlayerPawn>  PlayerPawnToSpawn;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<AGGCameraPawn>  CameraPawnToSpawn;


	
protected:
	void SpawnPlayerPawn(AGGPlayerController* InPlayerController);	// Handle spawning the Player Pawn
	void SpawnCameraPawn(AGGPlayerController* InPlayerController);

public:
	AGGGameModeBase();					// Default Constructor

	
	virtual void StartPlay() override; 	/** Transitions to calls BeginPlay on actors. */
};
