#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	// Setting the skeletal mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder (TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple"));
	if (SkeletalMeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshFinder.Object);
	}
	
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	// Camera Spring Arm
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("CameraSpringArm"));
	CameraSpringArm -> SetupAttachment(RootComponent);
	
	CameraSpringArm -> TargetArmLength = 300.0f;
	CameraSpringArm -> bUsePawnControlRotation = true;
	
	CameraSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	CameraSpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	
	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera -> SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	Camera -> bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Cast controller to APlayerController
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Cast input subsystem to EnhancedSubsystem
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedSubsystem -> AddMappingContext(DefaultContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent -> BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent -> BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent -> BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	}
}



/* -------------------- */
/*   CUSTOM FUNCTIONS   */
/* -------------------- */

// INPUT
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookingVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookingVector.X);
	AddControllerPitchInput(LookingVector.Y);	
}

