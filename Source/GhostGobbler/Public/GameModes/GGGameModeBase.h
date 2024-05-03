#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GGGameModeBase.generated.h"


class AGGPlayerController;
class AGGPlayerPawn;

UCLASS()
class GHOSTGOBBLER_API AGGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	FVector SpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<AGGPlayerPawn>  PlayerPawnToSpawn;
	
protected:
	void SpawnPlayerPawn(AGGPlayerController* InPlayerController);	// Handle spawning the PlayerPawr

public:
	AGGGameModeBase();					// Default Constructor

	
	virtual void StartPlay() override; 	/** Transitions to calls BeginPlay on actors. */
};
