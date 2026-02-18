#include "AmmoPickup.h"
#include "AttributeComponent.h"

AAmmoPickup::AAmmoPickup()
{
	AmmoAmount = 10;
}

bool AAmmoPickup::ApplyEffect(AActor* TargetActor)
{
	UAttributeComponent* AttrComp = TargetActor->FindComponentByClass<UAttributeComponent>();
	
	if (AttrComp)
	{
		AttrComp->AddAmmo(AmmoAmount);
		return true;
	}
	
	return false;
}
