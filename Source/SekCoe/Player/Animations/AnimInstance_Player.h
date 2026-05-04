#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SekCoe/Player/PlayerCharacter.h"
#include "AnimInstance_Player.generated.h"

/**
 * 
 */
UCLASS()
class SEKCOE_API UAnimInstance_Player : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
	ACharacter* OwnerCharacter;
	
public:
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	float Speed;
	
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	float VerticalVelocity;
	
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	bool bIsGrounded;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
