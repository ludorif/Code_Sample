// Copyright (C) Ludovic Riffiod 2020. All Rights Reserved.
#include "ActionRequestData.h"
#include "ActionRequest.h"

FActionRequestData::FActionRequestData(const FName NewRequestType)
{
	RequestType = NewRequestType.GetComparisonIndex();
}

const FActionRequest FActionRequestData::SerializeRequestData(AActor* Requestor)
{
	FActionRequest ActionRequest(RequestType);
	FBufferArchive ToBinary;
	SaveData(ToBinary, Requestor);
	ActionRequest.SerializedRequestData = ToBinary;
	return ActionRequest;
}

