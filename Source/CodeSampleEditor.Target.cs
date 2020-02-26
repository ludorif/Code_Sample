// Copyright (C) Ludovic Riffiod 2020. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CodeSampleEditorTarget : TargetRules
{
	public CodeSampleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "CodeSample" } );
	}
}
