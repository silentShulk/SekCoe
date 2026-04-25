#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Player.generated.h"

/**
 * 
 */
UCLASS()
class SEKCOE_API UAnimInstance_Player : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	float Speed;
	
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	bool bIsInAir;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
