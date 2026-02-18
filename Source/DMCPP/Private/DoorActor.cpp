#include "DoorActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ADoorActor::ADoorActor()
{
	PivotComp = CreateDefaultSubobject<USceneComponent>(TEXT("PivotComp"));
	RootComponent = PivotComp;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(PivotComp);
}

void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoorActor::ToggleDoor()
{
	bIsOpen = !bIsOpen;
	
	OnDoorStateChanged(bIsOpen); 
}
