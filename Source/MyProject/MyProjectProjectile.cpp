// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "HealthComponent.h"
#include <Components/BoxComponent.h>

AMyProjectProjectile::AMyProjectProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMyProjectProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AMyProjectProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Destroy();

		if (auto health_comp = OtherActor->GetComponentByClass<UHealthComponent>(); health_comp)
		{
			auto mesh_comp = OtherActor->GetComponentByClass<UStaticMeshComponent>();
			auto box_col_comp = OtherActor->GetComponentByClass<UBoxComponent>();

			if (mesh_comp && box_col_comp)
			{
				FVector scale = mesh_comp->GetRelativeScale3D();
				FVector col_scale = box_col_comp->GetRelativeScale3D();

				FVector new_scale = scale * 0.85f;
				FVector new_col_scale = col_scale * 0.85f;

				mesh_comp->SetRelativeScale3D(new_scale);
				box_col_comp->SetRelativeScale3D(new_col_scale);
			}

			health_comp->ApplyDamage(5, 16);
			health_comp->TryDestroyTarget(OtherActor);
		}
	}
}