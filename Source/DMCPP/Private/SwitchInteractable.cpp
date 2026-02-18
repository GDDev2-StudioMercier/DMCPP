#include "SwitchInteractable.h"
#include "DoorActor.h"

USwitchInteractable::USwitchInteractable()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USwitchInteractable::Interact()
{
	if (LinkedDoor)
	{
		LinkedDoor->ToggleDoor();
	}
}
