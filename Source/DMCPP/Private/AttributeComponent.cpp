#include "AttributeComponent.h"


UAttributeComponent::UAttributeComponent()
{
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	MaxAmmo = 30;
	CurrentAmmo = MaxAmmo;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
}
bool UAttributeComponent::ApplyHealthChange(float Delta)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
	return CurrentHealth > 0.0f;
}

void UAttributeComponent::AddAmmo(int32 Amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);
}

bool UAttributeComponent::TryConsumeAmmo(int32 Amount)
{
	if (CurrentAmmo >= Amount)
	{
		CurrentAmmo -= Amount;
		return true;
	}
	return false;
}
