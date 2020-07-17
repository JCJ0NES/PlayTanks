// Copyright Epic Games, Inc. All Rights Reserve

#include "PlayTanksProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"

APlayTanksProjectile::APlayTanksProjectile() 
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &APlayTanksProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->Friction = 0.f;
	ProjectileMovement->bBounceAngleAffectsFriction = false;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.f;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
	ProjectileMovement->SetPlaneConstraintEnabled(true);
	ProjectileMovement->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void APlayTanksProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Destroy projectile on second bounce. Or destroy object and projectile on first bounce for certain objects. 
	//Currently uses physics as a means to determine if it should be destroyed. I am trying to change this to something more practical so physics can still be used for something else.
	if (bHasBounced)
	{
		if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
		{
			OtherActor->Destroy();//AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
		}
		Destroy();
	}
	else if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
		Destroy();
	}
	else
	{
		bHasBounced = true;
	}

	// Only add impulse and destroy projectile if we hit a physics
	

	//Destroy();
}