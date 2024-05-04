#pragma once

#include "CoreMinimal.h"
#include "GGPickupBase.h"
#include "GGPickup_Pellet.generated.h"

UCLASS()
class GHOSTGOBBLER_API AGGPickup_Pellet : public AGGPickupBase
{
	GENERATED_BODY()


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickupPellet|Components")
	TObjectPtr<UStaticMeshComponent> PickupMesh;

	
public:
	AGGPickup_Pellet();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	

};
