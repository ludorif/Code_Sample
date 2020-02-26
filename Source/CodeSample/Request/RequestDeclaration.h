#pragma once
#include "ActionRequestData.h"

/// How to create new RequestAction : 
///		* DECLARE_REQUEST_ACTION_POINTER : only takes pointer on any instance replicated (custom or not)
///		* DECLARE_REQUEST_ACTION : only takes references of any type (custom or not)
/// Declare your new request action as : 
///	DECLARE_REQUEST_ACTION...(Name, Type1, VariableName1, Type2, VariableName2....);

DECLARE_REQUEST_ACTION(Jump);
DECLARE_REQUEST_ACTION_ONE_PARAM(Run, bool, bStartRunning);
DECLARE_REQUEST_ACTION_TWO_PARAMS(Example, uint8, Param1, FString, Param2);
DECLARE_REQUEST_ACTION_POINTER_ONE_PARAM(Attack, ACharacter*, Enemy);


