// Copyright (C) Ludovic Riffiod 2020. All Rights Reserved.

#include "CSCharacter.h"
#include "Components/InputComponent.h"
#include "Request/RequestDeclaration.h"

ACSCharacter::ACSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

#pragma region Inputs
void ACSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACSCharacter::JumpInput);
	PlayerInputComponent->BindAction("Suicide", IE_Pressed, this, &ACSCharacter::Suicide);

	PlayerInputComponent->BindAction<FBoolDelegate>("Run", IE_Pressed, this, &ACSCharacter::RunInput, true);
	PlayerInputComponent->BindAction<FBoolDelegate>("Run", IE_Released, this, &ACSCharacter::RunInput, false);
}

//Inputs below are meant to test different requests from client.
void ACSCharacter::RunInput(bool bStartRunning)
{
	TUniquePtr<FRun> Run = MakeUnique<FRun>(bStartRunning);
	Server_RequestAction(Run->SerializeRequestData(this));
}
void ACSCharacter::JumpInput()
{
	TUniquePtr<FJump> Jump = MakeUnique<FJump>();
	Server_RequestAction(Jump->SerializeRequestData(this));
}
void ACSCharacter::Suicide()
{
	//Use this to simulate an attack against himself, only for demo
	TUniquePtr<FAttack> Attack = MakeUnique<FAttack>(this);
	Server_RequestAction(Attack->SerializeRequestData(this));
}
#pragma endregion

#pragma region RPC
bool ACSCharacter::Server_RequestAction_Validate(const FActionRequest& RequestAction)
{
	return true;
}

/// <summary>
/// This function allows you to verify requests in a cheat free environment.
/// You can decide to allow them or not.
/// </summary>
void ACSCharacter::Server_RequestAction_Implementation(const FActionRequest& RequestAction)
{
	//Prevent any request on character while he is dead
	if (bIsDead)
	{
		return;
	}

	bool bShouldMulticast = false;
	const TSharedRef<FActionRequest> RequestActionCopy = MakeShared<FActionRequest>(RequestAction);

	if (RequestAction.IsSameType(NAME_Jump))
	{
		bShouldMulticast = true;
	}
	else if (RequestAction.IsSameType(NAME_Run))
	{
		const TUniquePtr<FRun> Run = MakeUnique<FRun>(RequestAction, this);
		if (Run->bStartRunning)
		{
			//Verify if player has enough stamina to execute this request
			if (StaminaPercent > 0)
			{
				bShouldMulticast = true;
				Speed *= SpeedMultiplier;
			}
		}
		else
		{
			bShouldMulticast = true;
			Speed /= SpeedMultiplier;
		}

		UE_LOG(LogTemp, Log, TEXT("New speed : %f"), Speed);
	}
	else if (RequestAction.IsSameType(NAME_Attack))
	{
		const TUniquePtr<FAttack> Attack = MakeUnique<FAttack>(RequestAction, this);

		//Prevent player to hurt himself
		if (ensureMsgf(Attack->Enemy != this, TEXT("Character %s try to hurt himself"), *Attack->Enemy->GetActorLabel()))
		{
			bShouldMulticast = true;
		}
	}

	if (bShouldMulticast)
	{
		//Some successful requests need to be multicasted to provide feedback(fx, animations...)
		Multicast_ActionResult(RequestActionCopy.Get());
	}
}

void ACSCharacter::Multicast_ActionResult_Implementation(const FActionRequest& RequestAction)
{
	if (HasAuthority())
	{
		//Server-side request logic should be done into Server_RequestAction to keep consistency
		return;
	}

	if (RequestAction.IsSameType(NAME_Jump))
	{
		if (Role == ROLE_AutonomousProxy)
		{
			Jump();
		}
	}
	else if (RequestAction.IsSameType(NAME_Run))
	{
		const TUniquePtr<FRun> Run = MakeUnique<FRun>(RequestAction, this);
		UE_LOG(LogTemp, Log, TEXT("%s running"), Run->bStartRunning ? TEXT("Start") : TEXT("End"));
		//Could be use to change animation state and spawn fx animations		
	}
	else if (RequestAction.IsSameType(NAME_Attack))
	{
		//Could be use to change animation state and spawn fx animations
	}
}
#pragma endregion



