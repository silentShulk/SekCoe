#include "AnimInstance_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"


void UAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (APawn* PawnOwner = TryGetPawnOwner())
	{
		Speed = PawnOwner->GetVelocity().Size();
		bIsInAir = PawnOwner->GetMovementComponent()->IsFalling();
	}
		
}