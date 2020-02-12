// Fill out your copyright notice in the Description page of Project Settings.

#include "BGCharacter.h"
#include "Engine.h"

// Sets default values
ABGCharacter::ABGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());

	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// Allow the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);
	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPSCameraComponent);
	// Disable some environmental shadowing to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void ABGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using BGCharacter and a lot of lube."));
	}
}

// Called every frame
void ABGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input, Make sure to also implement 
void ABGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &ABGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABGCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &ABGCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABGCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABGCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABGCharacter::StopJump);

}

void ABGCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ABGCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ABGCharacter::StartJump()
{
	bPressedJump = true;
}

void ABGCharacter::StopJump()
{
	bPressedJump = false;
}