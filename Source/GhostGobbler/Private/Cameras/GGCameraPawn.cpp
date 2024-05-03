#include "Cameras/GGCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGGCameraPawn::AGGCameraPawn()
{
	PrimaryActorTick.bCanEverTick = false;


	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp -> SetupAttachment(GetRootComponent());
	SpringArmComp -> bUsePawnControlRotation = false;

	
	CameraComp  = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp -> SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);


	bUseControllerRotationYaw = false;
	
}

void AGGCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGGCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGGCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

