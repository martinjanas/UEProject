// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorRotator.h"

// Sets default values for this component's properties
UDoorRotator::UDoorRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorRotator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* door = GetOwner();

    if (!door)
        return;

    UStaticMeshComponent* door_mesh_comp = Cast<UStaticMeshComponent>(door->GetDefaultSubobjectByName(TEXT("Door")));

    if (!door_mesh_comp)
        return;

    static FRotator initial_rotation = door_mesh_comp->GetRelativeRotation();
    static bool bIsOpening = true; // Flag to track whether the door is opening or closing

    FRotator target_rotation = bIsOpening ? initial_rotation + FRotator(0, 90, 0) : initial_rotation + FRotator(0, -90, 0);

    // If the door reaches the target rotation, toggle the opening/closing flag
    if (FMath::IsNearlyEqual(door_mesh_comp->GetRelativeRotation().Yaw, target_rotation.Yaw, 1.0f))
        bIsOpening = !bIsOpening;

    //FRotator new_rotation = FMath::InterpEaseInOut(door_mesh_comp->GetRelativeRotation(), target_rotation, DeltaTime, 0.8f);

    FRotator new_rotation = FMath::Lerp(door_mesh_comp->GetRelativeRotation(), target_rotation, DeltaTime * 2.0f); // You can adjust the speed by changing the multiplier

    door_mesh_comp->SetRelativeRotation(new_rotation);
}

