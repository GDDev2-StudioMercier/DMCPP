#include "Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->InitSphereRadius(50.0f);
	SphereComp->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(SphereComp))
	{
		SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
	}
}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							 bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	if (ApplyEffect(OtherActor))
	{
		PlayPickupFeedback();
		Destroy();
	}
}

void APickup::PlayPickupFeedback()
{
	//TODO sound/particle logic here
}
