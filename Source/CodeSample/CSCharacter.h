// Copyright (C) Ludovic Riffiod 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Request/ActionRequest.h"
#include "CSCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FBoolDelegate, bool);

UCLASS()
class CODESAMPLE_API ACSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACSCharacter();	
	
	UFUNCTION(Server, reliable, WithValidation)
		void Server_RequestAction(const FActionRequest& RequestAction);

private:
	UFUNCTION(NetMulticast, reliable)
		void Multicast_ActionResult(const FActionRequest& RequestAction);

	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void RunInput(bool bStartRunning);
	void JumpInput();
	void Suicide();

	bool bIsDead;
	float StaminaPercent = 1.0f;
	float Speed = 1.0f;

	const float SpeedMultiplier = 10;
};
