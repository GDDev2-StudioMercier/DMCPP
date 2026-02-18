#include "WeaponComponent.h"
#include "DMCPPProjectile.h"
#include "AttributeComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

UWeaponComponent::UWeaponComponent()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UWeaponComponent::Fire()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	UAttributeComponent* AttrComp = Owner->FindComponentByClass<UAttributeComponent>();
	if (AttrComp && !AttrComp->TryConsumeAmmo(1))
	{
		return;
	}

	// 2. Spawn Projectile
	if (ProjectileClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FVector SpawnLocation = Owner->GetActorLocation();
			FRotator SpawnRotation = Owner->GetActorRotation();

			// If owner is a character with a camera, use camera transform
			if (ACharacter* Character = Cast<ACharacter>(Owner))
			{
				// Attempt to find camera component for accurate aiming
				if (UCameraComponent* Camera = Character->FindComponentByClass<UCameraComponent>())
				{
					SpawnRotation = Camera->GetComponentRotation();
					SpawnLocation = Camera->GetComponentLocation() + (SpawnRotation.Vector() * MuzzleOffset.X) + (SpawnRotation.RotateVector(FVector(0, MuzzleOffset.Y, MuzzleOffset.Z)));
				}
			}

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = Owner;
			SpawnParams.Instigator = Cast<APawn>(Owner);

			World->SpawnActor<ADMCPPProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}

	// 3. Play Effects
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Owner->GetActorLocation());
	}
	
	if (FireAnimation)
	{
		if (ACharacter* Character = Cast<ACharacter>(Owner))
		{
			if (UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance())
			{
				AnimInstance->Montage_Play(FireAnimation, 1.0f);
			}
		}
	}
}
