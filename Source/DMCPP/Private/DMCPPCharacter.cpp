// Copyright Epic Games, Inc. All Rights Reserved.

#include "Public/DMCPPCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Public/DMCPP.h"

// --- INCLUDES ---
#include "SwitchInteractable.h"
#include "AttributeComponent.h"
#include "WeaponComponent.h" // Include the new component
#include "Engine/World.h"

ADMCPPCharacter::ADMCPPCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	AttributeComp = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComp"));
	
	// NEW: Initialize Weapon Component
	WeaponComp = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComp"));

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void ADMCPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{   
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
	   if (JumpAction)
	   {
		   EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ADMCPPCharacter::DoJumpStart);
		   EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADMCPPCharacter::DoJumpEnd);
	   }

	   if (MoveAction)
	   {
		   EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADMCPPCharacter::MoveInput);
	   }

	   if (LookAction)
	   {
		   EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADMCPPCharacter::LookInput);
	   }

	   if (MouseLookAction)
	   {
		   EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ADMCPPCharacter::LookInput);
	   }

	   if (InteractAction)
	   {
		   EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADMCPPCharacter::Interact);
	   }

	   if (ShootAction)
	   {
		   EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ADMCPPCharacter::Shoot);
	   }
	}
	else
	{
	   UE_LOG(LogDMCPP, Error, TEXT("'%s' Failed to find an Enhanced Input Component!"), *GetNameSafe(this));
	}
}

void ADMCPPCharacter::MoveInput(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void ADMCPPCharacter::LookInput(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoAim(LookAxisVector.X, LookAxisVector.Y);
}

void ADMCPPCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
	   AddControllerYawInput(Yaw);
	   AddControllerPitchInput(Pitch);
	}
}

void ADMCPPCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
	   AddMovementInput(GetActorRightVector(), Right);
	   AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ADMCPPCharacter::DoJumpStart()
{
	Jump();
}

void ADMCPPCharacter::DoJumpEnd()
{
	StopJumping();
}

void ADMCPPCharacter::Interact()
{
	if (!FirstPersonCameraComponent) return;

	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * 250.0f);

	FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
	   if (AActor* HitActor = Hit.GetActor())
	   {
		  USwitchInteractable* SwitchComp = HitActor->FindComponentByClass<USwitchInteractable>();
		  if (SwitchComp)
		  {
			 SwitchComp->Interact();
		  }
	   }
	}
}

void ADMCPPCharacter::Shoot()
{
	if (WeaponComp)
	{
		WeaponComp->Fire();
	}
}
