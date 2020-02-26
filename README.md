# Unreal Engine Multiplayer Code Sample
Implementation of an abstraction layer to simplify communication, force request security and use low weight messages

My code sample demonstrates how I implement, comment and explain C++ code for Unreal Engine. I use the coding standard from Unreal Engine's documentation.
The same concept can be applied to other engines and other languages.

# A. Low weight messages #
The structure FActionRequest defined into ActionRequest.h contains:

- Four-bytes RequestType int value corresponding to the ComparisonIndex of the request FName
- Bytes array containing serialized content.


The structure FActionRequestData defined into ActionRequestData.h and implemented into ActionRequestData.cpp contains:

- Functions to serialize / deserialize:
- Pointers to AActors (world instantiated objects)
- Copy of any data type
- Macro to create struct for any numbers of parameters:	
**I used macros instead of templates because templates are forbidden into Unreal Engine Remote Procedure Calls.**

# B. Simplify communication #
Macros declared into ActionRequestData.h allows to define easily structures with auto serialization for any type of parameters. You can see examples into RequestDeclaration.h.
Theses structures are passed into FActionRequest which allows to have one single RPC for all requests.

# C. Force security #
As shown into CSCharacter.h, the architecture always send request via RPC from client to server. 
The server can check conditions in a cheat free environment before deserializing data and using it only if needed.
After this validation, a multicast can be done to inform all players about changes on the request sender.

# How to test #
- Enable dedicated server into Unreal Engine multiplayer options
- There is 3 input linked to 3 different requests : 
	- Space will send a FJump request to the server : only the death of the player will be checked
	- Shift will send a FRun request to the server with bStartRunning value corresponding to the Pressed/ Released state of the button : sufficient stamina will be checked
	- Right mouse button will send a FAttack request to the server with the Enemy corresponding to the sender : comparison between sender and Enemy will be done to prevent suicide (this example aims at showing the pointer request use).
