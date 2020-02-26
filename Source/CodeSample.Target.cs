// Copyright (C) Ludovic Riffiod 2020. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CodeSampleTarget : TargetRules
{
	public CodeSampleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "CodeSample" } );
	}
}
