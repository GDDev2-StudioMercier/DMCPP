#include "HealthPickup.h"
#include "AttributeComponent.h"

AHealthPickup::AHealthPickup()
{
	HealthAmount = 50.0f;
}

bool AHealthPickup::ApplyEffect(AActor* TargetActor)
{
	UAttributeComponent* AttrComp = TargetActor->FindComponentByClass<UAttributeComponent>();
	
	if (AttrComp)
	{
		return AttrComp->ApplyHealthChange(HealthAmount);
	}
	
	return false;
}
