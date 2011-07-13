
// HeeksCNCTypes.h

#pragma once

// NOTE: If adding to this enumeration, please also update the HeeksCNCType() routine.

enum{
	ProgramType = 10001,
	NCCodeBlockType,
	NCCodeType,
	OperationsType,
	ProfileType,
	PocketType,
	ZigZagType,
	DrillingType,
	ToolType,
	ToolsType,
	CounterBoreType,
	FixtureType,
	FixturesType,
	SpeedReferenceType,
	SpeedReferencesType,
	CuttingRateType,
	PositioningType,
	BOMType,
	TrsfNCCodeType,
	ProbeCentreType,
	ProbeEdgeType,
	ChamferType,
	ProbeGridType,
	TagsType,
	TagType,
	ScriptOpType,
	AttachOpType,
	UnattachOpType,
	WaterlineType,
	TappingType,
	HeeksCNCMaximumType
};
