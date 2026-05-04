#include "AnimInstance_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"



void UAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if ((OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner())))
	{
		float RawSpeed = OwnerCharacter->GetVelocity().Size();
		Speed = FMath::FInterpTo(Speed, RawSpeed, DeltaSeconds, 7);
		
		VerticalVelocity = OwnerCharacter->GetVelocity().Z;
		
		bIsGrounded = !(OwnerCharacter->GetMovementComponent()->IsFalling());
	}
}
