#include "ErectusInclude.h"

mINI::INIFile file("Erectus.ini");
mINI::INIStructure ini;

OverlaySettingsA DefaultPlayerSettings
{
	true,					//Enabled
	1500,					//EnabledDistance
	true,					//DrawAlive
	{ 0.0f, 1.0f, 0.0f },	//AliveColor
	true,					//DrawDowned
	{ 1.0f, 1.0f, 0.0f },	//DownedColor
	false,					//DrawDead
	{ 1.0f, 0.0f, 0.0f },	//DeadColor
	false,					//DrawUnknown
	{ 1.0f, 0.5f, 0.0f },	//UnknownColor
	true,					//DrawEnabled;
	1.0f,					//EnabledAlpha;
	false,					//DrawDisabled;
	0.5f,					//DisabledAlpha;
	true,					//DrawNamed;
	false,					//DrawUnnamed;
	true,					//ShowName;
	true,					//ShowDistance;
	true,					//ShowHealth
	false,					//ShowDeadHealth
	true,					//TextShadowed;
	true,					//TextCentered;
};

OverlaySettingsA DefaultNpcSettings
{
	true,					//Enabled
	1500,					//EnabledDistance
	true,					//DrawAlive
	{ 0.5f, 1.0f, 1.0f },	//AliveColor
	false,					//DrawDowned
	{ 0.7f, 0.7f, 1.0f },	//DownedColor
	false,					//DrawDead
	{ 1.0f, 0.5f, 0.5f },	//DeadColor
	false,					//DrawUnknown
	{ 1.0f, 0.5f, 1.0f },	//UnknownColor
	true,					//DrawEnabled;
	1.0f,					//EnabledAlpha;
	false,					//DrawDisabled;
	0.5f,					//DisabledAlpha;
	true,					//DrawNamed;
	false,					//DrawUnnamed;
	true,					//ShowName;
	true,					//ShowDistance;
	true,					//ShowHealth
	false,					//ShowDeadHealth
	true,					//TextShadowed;
	true,					//TextCentered;
};

OverlaySettingsB DefaultOverlaySettingsB
{
	false,					//Enabled
	1500,					//EnabledDistance
	{ 1.0f, 1.0f, 1.0f },	//Color
	true,					//DrawEnabled
	1.0f,					//EnabledAlpha
	false,					//DrawDisabled
	0.5f,					//DisabledAlpha
	true,					//DrawNamed
	false,					//DrawUnnamed
	true,					//ShowName
	true,					//ShowDistance
	true,					//TextCentered
	true,					//TextShadowed
	{						//Whitelisted
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
	},
	{						//Whitelist
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	},
};

ScrapLooterSettings DefaultScrapLooterSettings
{
	false,
	false,
	false,
	false,
	30,
	60,
	3000,
	{
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
	},
	{
		0x00017DE8,//Black Titanium
		0x00017DE9,//Ultracite
		0x0001FA8C,//Acid
		0x0001FA91,//Aluminum
		0x0001FA94,//Ballistic Fiber
		0x0001FA96,//Antiseptic
		0x0001FA97,//Asbestos
		0x0001FA98,//Bone
		0x0001FA9A,//Ceramic
		0x0001FA9B,//Circuitry
		0x0001FA9C,//Copper
		0x0001FA9D,//Cork
		0x0001FA9F,//Crystal
		0x0001FAA0,//Fiber Optics
		0x0001FAA1,//Fiberglass
		0x0001FAA4,//Glass
		0x0001FAA5,//Adhesive
		0x0001FAA6,//Gold
		0x0001FAAD,//Lead
		0x0001FAAE,//Leather
		0x0001FAB0,//Gear
		0x0001FAB3,//Nuclear Material
		0x0001FAB4,//Oil
		0x0001FAB7,//Plastic
		0x0001FAB9,//Rubber
		0x0001FABB,//Silver
		0x0001FABC,//Spring
		0x0001FABD,//Steel
		0x0001FAC2,//Wood
		0x0003D294,//Screw
		0x0005A0C4,//Concrete
		0x0005A0C7,//Fertilizer
		0x001223C7,//Cloth
		0x002B9178,//Pure Cobalt Flux
		0x002B917A,//Pure Fluorescent Flux
		0x002B917C,//Pure Violet Flux
		0x002B917E,//Pure Crimson Flux
		0x002B9180,//Pure Yellowcake Flux
		0x0031C09A,//Coal
		0x0054E4FA,//Vault 94 Steel
	},
	{
		"Black Titanium",//0x00017DE8
		"Ultracite",//0x00017DE9
		"Acid",//0x0001FA8C
		"Aluminum",//0x0001FA91
		"Ballistic Fiber",//0x0001FA94
		"Antiseptic",//0x0001FA96
		"Asbestos",//0x0001FA97
		"Bone",//0x0001FA98
		"Ceramic",//0x0001FA9A
		"Circuitry",//0x0001FA9B
		"Copper",//0x0001FA9C
		"Cork",//0x0001FA9D
		"Crystal",//0x0001FA9F
		"Fiber Optics",//0x0001FAA0
		"Fiberglass",//0x0001FAA1
		"Glass",//0x0001FAA4
		"Adhesive",//0x0001FAA5
		"Gold",//0x0001FAA6
		"Lead",//0x0001FAAD
		"Leather",//0x0001FAAE
		"Gear",//0x0001FAB0
		"Nuclear Material",//0x0001FAB3
		"Oil",//0x0001FAB4
		"Plastic",//0x0001FAB7
		"Rubber",//0x0001FAB9
		"Silver",//0x0001FABB
		"Spring",//0x0001FABC
		"Steel",//0x0001FABD
		"Wood",//0x0001FAC2
		"Screw",//0x0003D294
		"Concrete",//0x0005A0C4
		"Fertilizer",//0x0005A0C7
		"Cloth",//0x001223C7
		"Pure Cobalt Flux",//0x002B9178
		"Pure Fluorescent Flux",//0x002B917A
		"Pure Violet Flux",//0x002B917C
		"Pure Crimson Flux",//0x002B917E
		"Pure Yellowcake Flux",//0x002B9180
		"Coal",//0x0031C09A
		"Vault 94 Steel",//0x0054E4FA
	},
};

ItemLooterSettings DefaultItemLooterSettings
{
	false,
	false,
	false,
	30,
	60,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	3000,
	false,
	{
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
	},
	{
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	},
	{
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
	},
	{
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	},
};

WeaponSettings DefaultWeaponSettings
{
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	250,
	false,
	2.0f,
	false,
	500.0f,
};

TargetSettings DefaultTargetSettings
{
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	20.0f,
	false,
	{ 1.0f, 0.0f, 1.0f },
	false,
	0,
	1,
	1,
	12,
};

LocalPlayerSettings DefaultLocalPlayerSettings
{
	false,
	false,
	524287,
	false,
	0.1f,
	false,
	false,
	false,
	false,
	90001,
	false,
	9001,
	false,
	9001,
	false,
	9001,
	false,
	9001,
	false,
	9001,
	false,
	9001,
	false,
	9001,
};

OpkSettings DefaultOpkSettings
{
	false,
	false,
};

UtilitySettings DefaultUtilitySettings
{
	false,
	false,
	0x00000000,
	0x00000000,
};

SwapperSettings DefaultSwapperSettings
{
	0x00000000,
	0x00000000,
};

TransferSettings DefaultTransferSettings
{
	0x00000000,
	0x00000000,
	true,
	true,
	{
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
	},
	{
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	},
	{
		true, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
	},
	{
		0x00021B3B, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	},
};

TeleportSettings DefaultTeleportSettings
{
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
	0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, false,
};

NukeCodeSettings DefaultNukeCodeSettings
{
	false,
	false,
	false,
	false,
};

LegendarySettings DefaultLegendarySettings
{
	true,
	{ 0.7f, 1.0f, 0.7f },
	true,
	{ 1.0f, 0.5f, 0.5f },
	true,
	{ 0.7f, 1.0f, 0.7f },
	true,
	{ 1.0f, 0.5f, 0.5f },
	true,
	{ 0.7f, 1.0f, 0.7f },
	true,
	{ 1.0f, 0.5f, 0.5f },
};

FluxSettings DefaultFluxSettings
{
	false,
	false,
	false,
	false,
	false,
};

EntityLooterSettings DefaultEntityLooterSettings
{
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	{
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
	},
	{
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	},
	{
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
	},
	{
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	},
};

HarvesterSettings DefaultHarvesterSettings
{
	false,
	false,
	false,
	{
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
	},
	{
		0x002DDD45,//Raw Crimson Flux
		0x002DDD46,//Raw Cobalt Flux
		0x002DDD49,//Raw Yellowcake Flux
		0x002DDD4B,//Raw Fluorescent Flux
		0x002DDD4D,//Raw Violet Flux
		0x00017F81,//Black Titanium Ore
		0x00019D29,//Aluminum Ore
		0x00019E36,//Gold Ore
		0x00019E51,//Copper Ore
		0x00065304,//Iron Ore
		0x00065324,//Lead Ore
		0x00065328,//Silver Ore
		0x00065338,//Uranium Ore
		0x00139013,//Ultracite Ore
		0x00058AA8,//Coal
		0x0016FAD8,//Unrefined Coal
		0x0056AAD2,//Irradiated Ore
		0x0000BAEF,//Wild Blackberry
		0x000F742E,//Carrot
		0x000330F8,//Corn
		0x000EF24D,//Gourd
		0x000FAFEB,//Melon
		0x00033102,//Mutfruit
		0x000E0043,//Razorgrain
		0x0009DCC4,//Tato
		0x000183C6,//Junk Pile
		0x000731A3,//Wood Scraps
		0x00106D99,//Concrete Scrap
		0x001BF732,//Waste Oil
		0x001BF72D,//Waste Acid
		0x00015C61,//Raw Crystal
		0x001BF730,//Raw Fertilizer
		0x0010D90E,//Cranberries
		0x001FABC2,//Diseased Cranberries
		0x000D981D,//Tarberry
		0x0012C48E,//Firecracker Berry
		0x001F24B6,//Melon Blossom
		0x001C400D,//Tato Flower
		0x001C4013,//Carrot Flower
		0x001C4011,//Gourd Blossom
		0x001C0FC2,//Brain Fungus
		0x001C0FC3,//Glowing Fungus
		0x001C25EE,//Bloodleaf
		0x001BE2AB,//Silt Bean
		0x001C3FDC,//Soot Flower
		0x003C51E0,//Toxic Soot Flower
		0x0009F24B,//Thistle
		0x00525644,//Rhododendron Flower
		0x00064AF0,//Firecap
		0x003C51DF,//Snaptail Reed
		0x00384D8C,//Starlight Berries
		0x000E34E9,//Mutated Fern Flower
		0x00111346,//Lure Weed
		0x00110A12,//Aster
		0x00111345,//Blight
		0x00113106,//Fever Blossom
		0x003FFADB,//Kaleidopore Flower
		0x0011C0C2,//Ash Rose
		0x00412186,//Gut Shroom
		0x00088C3C,//Pumpkin
		0x004EE5D2,//Ginseng Root
		0x003B90A2,//Digested Goo
		0x00081FDB,//Strangler Bloom
		0x00050DC9,//Strangler Pod
		0x003D7496,//Swamp Plant
		0x003D202D,//Bleach Dogwood
		0x00142950,//Megasloth Mushroom
		0x000933EA,//Glowing Resin
		0x0008E922,//Mothman Egg
	},
	{
		"Raw Crimson Flux",
		"Raw Cobalt Flux",
		"Raw Yellowcake Flux",
		"Raw Fluorescent Flux",
		"Raw Violet Flux",
		"Black Titanium Ore",
		"Aluminum Ore",
		"Gold Ore",
		"Copper Ore",
		"Iron Ore",
		"Lead Ore",
		"Silver Ore",
		"Uranium Ore",
		"Ultracite Ore",
		"Coal",
		"Unrefined Coal",
		"Irradiated Ore",
		"Wild Blackberry",
		"Carrot",
		"Corn",
		"Gourd",
		"Melon",
		"Mutfruit",
		"Razorgrain",
		"Tato",
		"Junk Pile",
		"Wood Scraps",
		"Concrete Scrap",
		"Waste Oil",
		"Waste Acid",
		"Raw Crystal",
		"Raw Fertilizer",
		"Cranberries",
		"Diseased Cranberries",
		"Tarberry",
		"Firecracker Berry",
		"Melon Blossom",
		"Tato Flower",
		"Carrot Flower",
		"Gourd Blossom",
		"Brain Fungus",
		"Glowing Fungus",
		"Bloodleaf",
		"Silt Bean",
		"Soot Flower",
		"Toxic Soot Flower",
		"Thistle",
		"Rhododendron Flower",
		"Firecap",
		"Snaptail Reed",
		"Starlight Berries",
		"Mutated Fern Flower",
		"Lure Weed",
		"Aster",
		"Blight",
		"Fever Blossom",
		"Kaleidopore Flower",
		"Ash Rose",
		"Gut Shroom",
		"Pumpkin",
		"Ginseng Root",
		"Digested Goo",
		"Strangler Bloom",
		"Strangler Pod",
		"Swamp Plant",
		"Bleach Dogwood",
		"Megasloth Mushroom",
		"Glowing Resin",
		"Mothman Egg",
	},
};

KnownRecipeSettings DefaultKnownRecipeSettings
{
	true,
	true,
};

MeleeSettings DefaultMeleeSettings
{
	false,
	10,
	20,
};

ChargenSettings DefaultChargenSettings
{
	false,
	0.33f,
	0.33f,
	0.33f,
};

ExtraNPCSettings DefaultExtraNPCSettings
{
	false,
	false,
	false,
	false,
	false,
	{
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
	},
	{
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	},
};

OverlaySettingsA PlayerSettings = DefaultPlayerSettings;
OverlaySettingsA NpcSettings = DefaultNpcSettings;
OverlaySettingsB ContainerSettings = DefaultOverlaySettingsB;
OverlaySettingsB JunkSettings = DefaultOverlaySettingsB;
OverlaySettingsB PlanSettings = DefaultOverlaySettingsB;
OverlaySettingsB MagazineSettings = DefaultOverlaySettingsB;
OverlaySettingsB BobbleheadSettings = DefaultOverlaySettingsB;
OverlaySettingsB ItemSettings = DefaultOverlaySettingsB;
OverlaySettingsB FloraSettings = DefaultOverlaySettingsB;
OverlaySettingsB EntitySettings = DefaultOverlaySettingsB;
ScrapLooterSettings CustomScrapLooterSettings = DefaultScrapLooterSettings;
ItemLooterSettings CustomItemLooterSettings = DefaultItemLooterSettings;
WeaponSettings CustomWeaponSettings = DefaultWeaponSettings;
TargetSettings CustomTargetSettings = DefaultTargetSettings;
LocalPlayerSettings CustomLocalPlayerSettings = DefaultLocalPlayerSettings;
OpkSettings CustomOpkSettings = DefaultOpkSettings;
UtilitySettings CustomUtilitySettings = DefaultUtilitySettings;
SwapperSettings CustomSwapperSettings = DefaultSwapperSettings;
TransferSettings CustomTransferSettings = DefaultTransferSettings;
TeleportSettings CustomTeleportSettings = DefaultTeleportSettings;
NukeCodeSettings CustomNukeCodeSettings = DefaultNukeCodeSettings;
LegendarySettings CustomLegendarySettings = DefaultLegendarySettings;
FluxSettings CustomFluxSettings = DefaultFluxSettings;
EntityLooterSettings NPCLooterSettings = DefaultEntityLooterSettings;
EntityLooterSettings ContainerLooterSettings = DefaultEntityLooterSettings;
HarvesterSettings CustomHarvesterSettings = DefaultHarvesterSettings;
KnownRecipeSettings CustomKnownRecipeSettings = DefaultKnownRecipeSettings;
MeleeSettings CustomMeleeSettings = DefaultMeleeSettings;
ChargenSettings CustomChargenSettings = DefaultChargenSettings;
ExtraNPCSettings CustomExtraNPCSettings = DefaultExtraNPCSettings;

void GetDWORD(const char *Section, const char *Key, DWORD *Value, DWORD *Default)
{
	if (!ini.has(Section))
	{
		ini[Section];
	}

	if (!ini[Section].has(Key))
	{
		char DefaultText[sizeof("00000000")];
		sprintf_s(DefaultText, "%08lX", *Default);
		ini[Section][Key] = DefaultText;
	}

	try
	{
		*Value = stoul(ini[Section][Key], nullptr, 16);
	}
	catch (...)
	{
		*Value = *Default;
	}
}

void SetDWORD(const char *Section, const char *Key, DWORD *Value, DWORD *Default)
{
	if (!ini.has(Section))
	{
		ini[Section];
	}

	if (!ini[Section].has(Key))
	{
		char DefaultText[sizeof("00000000")];
		sprintf_s(DefaultText, "%08lX", *Default);
		ini[Section][Key] = DefaultText;
	}

	char ValueText[sizeof("00000000")];
	sprintf_s(ValueText, "%08lX", *Value);
	ini[Section][Key] = ValueText;
}

void GetInt(const char *Section, const char *Key, int *Value, int *Default)
{
	if (!ini.has(Section))
	{
		ini[Section];
	}

	if (!ini[Section].has(Key))
	{
		ini[Section][Key] = std::to_string(*Default);
	}

	try
	{
		*Value = stoi(ini[Section][Key]);
	}
	catch (...)
	{
		*Value = *Default;
	}
}

void SetInt(const char *Section, const char *Key, int *Value, int *Default)
{
	if (!ini.has(Section))
	{
		ini[Section];
	}

	if (!ini[Section].has(Key))
	{
		ini[Section][Key] = std::to_string(*Default);
	}

	ini[Section][Key] = std::to_string(*Value);
}

void GetSliderInt(const char *Section, const char *Key, int *Value, int *Default, int Min, int Max)
{
	ValidateInt(Default, Min, Max);
	GetInt(Section, Key, Value, Default);
	ValidateInt(Value, Min, Max);
	SetInt(Section, Key, Value, Default);
}

void SetSliderInt(const char *Section, const char *Key, int *Value, int *Default, int Min, int Max)
{
	ValidateInt(Value, Min, Max);
	ValidateInt(Default, Min, Max);
	SetInt(Section, Key, Value, Default);
}

void GetFloat(const char *Section, const char *Key, float *Value, float *Default)
{
	if (!ini.has(Section))
	{
		ini[Section];
	}

	if (!ini[Section].has(Key))
	{
		ini[Section][Key] = std::to_string(*Default);
	}

	try
	{
		*Value = stof(ini[Section][Key]);
	}
	catch (...)
	{
		*Value = *Default;
	}
}

void SetFloat(const char *Section, const char *Key, float *Value, float *Default)
{
	if (!ini.has(Section))
	{
		ini[Section];
	}

	if (!ini[Section].has(Key))
	{
		ini[Section][Key] = std::to_string(*Default);
	}

	ini[Section][Key] = std::to_string(*Value);
}

void GetSliderFloat(const char *Section, const char *Key, float *Value, float *Default, float Min, float Max)
{
	ValidateFloat(Default, Min, Max);
	GetFloat(Section, Key, Value, Default);
	ValidateFloat(Value, Min, Max);
	SetFloat(Section, Key, Value, Default);
}

void SetSliderFloat(const char *Section, const char *Key, float *Value, float *Default, float Min, float Max)
{
	ValidateFloat(Value, Min, Max);
	ValidateFloat(Default, Min, Max);
	SetFloat(Section, Key, Value, Default);
}

void GetRGB(const char *Section, const char *Key, float *Value, float *Default)
{
	int KeyLength = GetTextLength(Key);
	int KeySize = KeyLength + sizeof("x");

	char *KeyR = new char[KeySize];
	sprintf_s(KeyR, KeySize, "%sR", Key);

	char *KeyG = new char[KeySize];
	sprintf_s(KeyG, KeySize, "%sG", Key);

	char *KeyB = new char[KeySize];
	sprintf_s(KeyB, KeySize, "%sB", Key);

	ValidateRGB(Default);
	GetFloat(Section, KeyR, &Value[0], &Default[0]);
	GetFloat(Section, KeyG, &Value[1], &Default[1]);
	GetFloat(Section, KeyB, &Value[2], &Default[2]);
	ValidateRGB(Value);

	delete[]KeyR;
	KeyR = nullptr;

	delete[]KeyG;
	KeyG = nullptr;

	delete[]KeyB;
	KeyB = nullptr;
}

void SetRGB(const char *Section, const char *Key, float *Value, float *Default)
{
	int KeyLength = GetTextLength(Key);
	int KeySize = KeyLength + sizeof("x");

	char *KeyR = new char[KeySize];
	sprintf_s(KeyR, KeySize, "%sR", Key);

	char *KeyG = new char[KeySize];
	sprintf_s(KeyG, KeySize, "%sG", Key);

	char *KeyB = new char[KeySize];
	sprintf_s(KeyB, KeySize, "%sB", Key);

	ValidateRGB(Value);
	ValidateRGB(Default);
	SetFloat(Section, KeyR, &Value[0], &Default[0]);
	SetFloat(Section, KeyG, &Value[1], &Default[1]);
	SetFloat(Section, KeyB, &Value[2], &Default[2]);

	delete[]KeyR;
	KeyR = nullptr;

	delete[]KeyG;
	KeyG = nullptr;

	delete[]KeyB;
	KeyB = nullptr;
}

void GetQuadFloat(const char *Section, const char *Key, float *Value, float *Default)
{
	int KeyLength = GetTextLength(Key);
	int KeySize = KeyLength + sizeof("x");

	char *KeyX = new char[KeySize];
	sprintf_s(KeyX, KeySize, "%sX", Key);

	char *KeyY = new char[KeySize];
	sprintf_s(KeyY, KeySize, "%sY", Key);

	char *KeyZ = new char[KeySize];
	sprintf_s(KeyZ, KeySize, "%sZ", Key);

	char *KeyW = new char[KeySize];
	sprintf_s(KeyW, KeySize, "%sW", Key);

	GetFloat(Section, KeyX, &Value[0], &Default[0]);
	GetFloat(Section, KeyY, &Value[1], &Default[1]);
	GetFloat(Section, KeyZ, &Value[2], &Default[2]);
	GetFloat(Section, KeyW, &Value[3], &Default[3]);

	delete[]KeyX;
	KeyX = nullptr;

	delete[]KeyY;
	KeyY = nullptr;

	delete[]KeyZ;
	KeyZ = nullptr;

	delete[]KeyW;
	KeyW = nullptr;
}

void SetQuadFloat(const char *Section, const char *Key, float *Value, float *Default)
{
	int KeyLength = GetTextLength(Key);
	int KeySize = KeyLength + sizeof("x");

	char *KeyX = new char[KeySize];
	sprintf_s(KeyX, KeySize, "%sX", Key);

	char *KeyY = new char[KeySize];
	sprintf_s(KeyY, KeySize, "%sY", Key);

	char *KeyZ = new char[KeySize];
	sprintf_s(KeyZ, KeySize, "%sZ", Key);

	char *KeyW = new char[KeySize];
	sprintf_s(KeyW, KeySize, "%sW", Key);

	SetFloat(Section, KeyX, &Value[0], &Default[0]);
	SetFloat(Section, KeyY, &Value[1], &Default[1]);
	SetFloat(Section, KeyZ, &Value[2], &Default[2]);
	SetFloat(Section, KeyW, &Value[3], &Default[3]);

	delete[]KeyX;
	KeyX = nullptr;

	delete[]KeyY;
	KeyY = nullptr;

	delete[]KeyZ;
	KeyZ = nullptr;

	delete[]KeyW;
	KeyW = nullptr;
}

void GetBool(const char *Section, const char *Key, bool *Value, bool *Default)
{
	int BufferValue = int(*Value);
	int BufferDefault = int(*Default);
	GetSliderInt(Section, Key, &BufferValue, &BufferDefault, 0, 1);
	*Value = bool(BufferValue);
}

void SetBool(const char *Section, const char *Key, bool *Value, bool *Default)
{
	int BufferValue = int(*Value);
	int BufferDefault = int(*Default);
	SetSliderInt(Section, Key, &BufferValue, &BufferDefault, 0, 1);
}

void GetOverlaySettingsA(const char *Section, OverlaySettingsA* Value, OverlaySettingsA* Default)
{
	GetBool(Section, "Enabled", &Value->Enabled, &Default->Enabled);
	GetSliderInt(Section, "EnabledDistance", &Value->EnabledDistance, &Default->EnabledDistance, 0, 3000);
	GetBool(Section, "DrawAlive", &Value->DrawAlive, &Default->DrawAlive);
	GetRGB(Section, "AliveColor", Value->AliveColor, Default->AliveColor);
	GetBool(Section, "DrawDowned", &Value->DrawDowned, &Default->DrawDowned);
	GetRGB(Section, "DownedColor", Value->DownedColor, Default->DownedColor);
	GetBool(Section, "DrawDead", &Value->DrawDead, &Default->DrawDead);
	GetRGB(Section, "DeadColor", Value->DeadColor, Default->DeadColor);
	GetBool(Section, "DrawUnknown", &Value->DrawUnknown, &Default->DrawUnknown);
	GetRGB(Section, "UnknownColor", Value->UnknownColor, Default->UnknownColor);
	GetBool(Section, "DrawEnabled", &Value->DrawEnabled, &Default->DrawEnabled);
	GetSliderFloat(Section, "EnabledAlpha", &Value->EnabledAlpha, &Default->EnabledAlpha, 0.0f, 1.0f);
	GetBool(Section, "DrawDisabled", &Value->DrawDisabled, &Default->DrawDisabled);
	GetSliderFloat(Section, "DisabledAlpha", &Value->DisabledAlpha, &Default->DisabledAlpha, 0.0f, 1.0f);
	GetBool(Section, "DrawNamed", &Value->DrawNamed, &Default->DrawNamed);
	GetBool(Section, "DrawUnnamed", &Value->DrawUnnamed, &Default->DrawUnnamed);
	GetBool(Section, "ShowName", &Value->ShowName, &Default->ShowName);
	GetBool(Section, "ShowDistance", &Value->ShowDistance, &Default->ShowDistance);
	GetBool(Section, "ShowHealth", &Value->ShowHealth, &Default->ShowHealth);
	GetBool(Section, "ShowDeadHealth", &Value->ShowDeadHealth, &Default->ShowDeadHealth);
	GetBool(Section, "TextShadowed", &Value->TextShadowed, &Default->TextShadowed);
	GetBool(Section, "TextCentered", &Value->TextCentered, &Default->TextCentered);
}

void SetOverlaySettingsA(const char *Section, OverlaySettingsA* Value, OverlaySettingsA* Default)
{
	SetBool(Section, "Enabled", &Value->Enabled, &Default->Enabled);
	SetSliderInt(Section, "EnabledDistance", &Value->EnabledDistance, &Default->EnabledDistance, 0, 3000);
	SetBool(Section, "DrawAlive", &Value->DrawAlive, &Default->DrawAlive);
	SetRGB(Section, "AliveColor", Value->AliveColor, Default->AliveColor);
	SetBool(Section, "DrawDowned", &Value->DrawDowned, &Default->DrawDowned);
	SetRGB(Section, "DownedColor", Value->DownedColor, Default->DownedColor);
	SetBool(Section, "DrawDead", &Value->DrawDead, &Default->DrawDead);
	SetRGB(Section, "DeadColor", Value->DeadColor, Default->DeadColor);
	SetBool(Section, "DrawUnknown", &Value->DrawUnknown, &Default->DrawUnknown);
	SetRGB(Section, "UnknownColor", Value->UnknownColor, Default->UnknownColor);
	SetBool(Section, "DrawEnabled", &Value->DrawEnabled, &Default->DrawEnabled);
	SetSliderFloat(Section, "EnabledAlpha", &Value->EnabledAlpha, &Default->EnabledAlpha, 0.0f, 1.0f);
	SetBool(Section, "DrawDisabled", &Value->DrawDisabled, &Default->DrawDisabled);
	SetSliderFloat(Section, "DisabledAlpha", &Value->DisabledAlpha, &Default->DisabledAlpha, 0.0f, 1.0f);
	SetBool(Section, "DrawNamed", &Value->DrawNamed, &Default->DrawNamed);
	SetBool(Section, "DrawUnnamed", &Value->DrawUnnamed, &Default->DrawUnnamed);
	SetBool(Section, "ShowName", &Value->ShowName, &Default->ShowName);
	SetBool(Section, "ShowDistance", &Value->ShowDistance, &Default->ShowDistance);
	SetBool(Section, "ShowHealth", &Value->ShowHealth, &Default->ShowHealth);
	SetBool(Section, "ShowDeadHealth", &Value->ShowDeadHealth, &Default->ShowDeadHealth);
	SetBool(Section, "TextShadowed", &Value->TextShadowed, &Default->TextShadowed);
	SetBool(Section, "TextCentered", &Value->TextCentered, &Default->TextCentered);
}

void GetOverlaySettingsB(const char *Section, OverlaySettingsB* Value, OverlaySettingsB* Default)
{
	GetBool(Section, "Enabled", &Value->Enabled, &Default->Enabled);
	GetSliderInt(Section, "EnabledDistance", &Value->EnabledDistance, &Default->EnabledDistance, 0, 3000);
	GetRGB(Section, "Color", Value->Color, Default->Color);
	GetBool(Section, "DrawEnabled", &Value->DrawEnabled, &Default->DrawEnabled);
	GetSliderFloat(Section, "EnabledAlpha", &Value->EnabledAlpha, &Default->EnabledAlpha, 0.0f, 1.0f);
	GetBool(Section, "DrawDisabled", &Value->DrawDisabled, &Default->DrawDisabled);
	GetSliderFloat(Section, "DisabledAlpha", &Value->DisabledAlpha, &Default->DisabledAlpha, 0.0f, 1.0f);
	GetBool(Section, "DrawNamed", &Value->DrawNamed, &Default->DrawNamed);
	GetBool(Section, "DrawUnnamed", &Value->DrawUnnamed, &Default->DrawUnnamed);
	GetBool(Section, "ShowName", &Value->ShowName, &Default->ShowName);
	GetBool(Section, "ShowDistance", &Value->ShowDistance, &Default->ShowDistance);
	GetBool(Section, "TextShadowed", &Value->TextShadowed, &Default->TextShadowed);
	GetBool(Section, "TextCentered", &Value->TextCentered, &Default->TextCentered);
	for (int i = 0; i < 32; i++)
	{
		char WhitelistedText[sizeof("Whitelisted31")];
		char WhitelistText[sizeof("Whitelist31")];
		sprintf_s(WhitelistedText, "Whitelisted%d", i);
		sprintf_s(WhitelistText, "Whitelist%d", i);
		GetBool(Section, WhitelistedText, &Value->Whitelisted[i], &Default->Whitelisted[i]);
		GetDWORD(Section, WhitelistText, &Value->Whitelist[i], &Default->Whitelist[i]);
	}
}

void SetOverlaySettingsB(const char *Section, OverlaySettingsB* Value, OverlaySettingsB* Default)
{
	SetBool(Section, "Enabled", &Value->Enabled, &Default->Enabled);
	SetSliderInt(Section, "EnabledDistance", &Value->EnabledDistance, &Default->EnabledDistance, 0, 3000);
	SetRGB(Section, "Color", Value->Color, Default->Color);
	SetBool(Section, "DrawEnabled", &Value->DrawEnabled, &Default->DrawEnabled);
	SetSliderFloat(Section, "EnabledAlpha", &Value->EnabledAlpha, &Default->EnabledAlpha, 0.0f, 1.0f);
	SetBool(Section, "DrawDisabled", &Value->DrawDisabled, &Default->DrawDisabled);
	SetSliderFloat(Section, "DisabledAlpha", &Value->DisabledAlpha, &Default->DisabledAlpha, 0.0f, 1.0f);
	SetBool(Section, "DrawNamed", &Value->DrawNamed, &Default->DrawNamed);
	SetBool(Section, "DrawUnnamed", &Value->DrawUnnamed, &Default->DrawUnnamed);
	SetBool(Section, "ShowName", &Value->ShowName, &Default->ShowName);
	SetBool(Section, "ShowDistance", &Value->ShowDistance, &Default->ShowDistance);
	SetBool(Section, "TextShadowed", &Value->TextShadowed, &Default->TextShadowed);
	SetBool(Section, "TextCentered", &Value->TextCentered, &Default->TextCentered);
	for (int i = 0; i < 32; i++)
	{
		char WhitelistedText[sizeof("Whitelisted31")];
		char WhitelistText[sizeof("Whitelist31")];
		sprintf_s(WhitelistedText, "Whitelisted%d", i);
		sprintf_s(WhitelistText, "Whitelist%d", i);
		SetBool(Section, WhitelistedText, &Value->Whitelisted[i], &Default->Whitelisted[i]);
		SetDWORD(Section, WhitelistText, &Value->Whitelist[i], &Default->Whitelist[i]);
	}
}

void GetScrapSettings()
{
	GetBool("ScrapSettings", "ScrapKeybindEnabled", &CustomScrapLooterSettings.ScrapKeybindEnabled, &DefaultScrapLooterSettings.ScrapKeybindEnabled);
	GetBool("ScrapSettings", "ScrapOverrideEnabled", &CustomScrapLooterSettings.ScrapOverrideEnabled, &DefaultScrapLooterSettings.ScrapOverrideEnabled);
	GetBool("ScrapSettings", "ScrapAutomaticLootingEnabled", &CustomScrapLooterSettings.ScrapAutomaticLootingEnabled, &DefaultScrapLooterSettings.ScrapAutomaticLootingEnabled);
	GetBool("ScrapSettings", "ScrapAutomaticStatus", &CustomScrapLooterSettings.ScrapAutomaticStatus, &DefaultScrapLooterSettings.ScrapAutomaticStatus);
	GetSliderInt("ScrapSettings", "ScrapAutomaticSpeedMin", &CustomScrapLooterSettings.ScrapAutomaticSpeedMin, &DefaultScrapLooterSettings.ScrapAutomaticSpeedMin, 10, 60);
	GetSliderInt("ScrapSettings", "ScrapAutomaticSpeedMax", &CustomScrapLooterSettings.ScrapAutomaticSpeedMax, &DefaultScrapLooterSettings.ScrapAutomaticSpeedMax, 10, 60);
	GetSliderInt("ScrapSettings", "ScrapLooterDistance", &CustomScrapLooterSettings.ScrapLooterDistance, &DefaultScrapLooterSettings.ScrapLooterDistance, 0, 3000);
	for (int i = 0; i < 40; i++)
	{
		char ScrapEnabledText[sizeof("ScrapEnabled39")];
		sprintf_s(ScrapEnabledText, "ScrapEnabled%d", i);
		GetBool("ScrapSettings", ScrapEnabledText, &CustomScrapLooterSettings.ScrapEnabledList[i], &DefaultScrapLooterSettings.ScrapEnabledList[i]);
	}
	if (CustomScrapLooterSettings.ScrapAutomaticSpeedMax < CustomScrapLooterSettings.ScrapAutomaticSpeedMin)
	{
		CustomScrapLooterSettings.ScrapAutomaticSpeedMax = CustomScrapLooterSettings.ScrapAutomaticSpeedMin;
	}
}

void SetScrapSettings()
{
	if (CustomScrapLooterSettings.ScrapAutomaticSpeedMax < CustomScrapLooterSettings.ScrapAutomaticSpeedMin)
	{
		CustomScrapLooterSettings.ScrapAutomaticSpeedMax = CustomScrapLooterSettings.ScrapAutomaticSpeedMin;
	}
	SetBool("ScrapSettings", "ScrapKeybindEnabled", &CustomScrapLooterSettings.ScrapKeybindEnabled, &DefaultScrapLooterSettings.ScrapKeybindEnabled);
	SetBool("ScrapSettings", "ScrapOverrideEnabled", &CustomScrapLooterSettings.ScrapOverrideEnabled, &DefaultScrapLooterSettings.ScrapOverrideEnabled);
	SetBool("ScrapSettings", "ScrapAutomaticLootingEnabled", &CustomScrapLooterSettings.ScrapAutomaticLootingEnabled, &DefaultScrapLooterSettings.ScrapAutomaticLootingEnabled);
	SetBool("ScrapSettings", "ScrapAutomaticStatus", &CustomScrapLooterSettings.ScrapAutomaticStatus, &DefaultScrapLooterSettings.ScrapAutomaticStatus);
	SetSliderInt("ScrapSettings", "ScrapAutomaticSpeedMin", &CustomScrapLooterSettings.ScrapAutomaticSpeedMin, &DefaultScrapLooterSettings.ScrapAutomaticSpeedMin, 10, 60);
	SetSliderInt("ScrapSettings", "ScrapAutomaticSpeedMax", &CustomScrapLooterSettings.ScrapAutomaticSpeedMax, &DefaultScrapLooterSettings.ScrapAutomaticSpeedMax, 10, 60);
	SetSliderInt("ScrapSettings", "ScrapLooterDistance", &CustomScrapLooterSettings.ScrapLooterDistance, &DefaultScrapLooterSettings.ScrapLooterDistance, 0, 3000);
	for (int i = 0; i < 40; i++)
	{
		char ScrapEnabledText[sizeof("ScrapEnabled39")];
		sprintf_s(ScrapEnabledText, "ScrapEnabled%d", i);
		SetBool("ScrapSettings", ScrapEnabledText, &CustomScrapLooterSettings.ScrapEnabledList[i], &DefaultScrapLooterSettings.ScrapEnabledList[i]);
	}
}

void GetItemLooterSettings()
{
	GetBool("ItemLooterSettings", "ItemKeybindEnabled", &CustomItemLooterSettings.ItemKeybindEnabled, &DefaultItemLooterSettings.ItemKeybindEnabled);
	GetBool("ItemLooterSettings", "ItemAutomaticLootingEnabled", &CustomItemLooterSettings.ItemAutomaticLootingEnabled, &DefaultItemLooterSettings.ItemAutomaticLootingEnabled);
	GetBool("ItemLooterSettings", "ItemAutomaticStatus", &CustomItemLooterSettings.ItemAutomaticStatus, &DefaultItemLooterSettings.ItemAutomaticStatus);
	GetSliderInt("ItemLooterSettings", "ItemAutomaticSpeedMin", &CustomItemLooterSettings.ItemAutomaticSpeedMin, &DefaultItemLooterSettings.ItemAutomaticSpeedMin, 10, 60);
	GetSliderInt("ItemLooterSettings", "ItemAutomaticSpeedMax", &CustomItemLooterSettings.ItemAutomaticSpeedMax, &DefaultItemLooterSettings.ItemAutomaticSpeedMax, 10, 60);
	GetBool("ItemLooterSettings", "ItemLooterWeaponsEnabled", &CustomItemLooterSettings.ItemLooterWeaponsEnabled, &DefaultItemLooterSettings.ItemLooterWeaponsEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterWeaponsDistance", &CustomItemLooterSettings.ItemLooterWeaponsDistance, &DefaultItemLooterSettings.ItemLooterWeaponsDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterArmorEnabled", &CustomItemLooterSettings.ItemLooterArmorEnabled, &DefaultItemLooterSettings.ItemLooterArmorEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterArmorDistance", &CustomItemLooterSettings.ItemLooterArmorDistance, &DefaultItemLooterSettings.ItemLooterArmorDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterAmmoEnabled", &CustomItemLooterSettings.ItemLooterAmmoEnabled, &DefaultItemLooterSettings.ItemLooterAmmoEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterAmmoDistance", &CustomItemLooterSettings.ItemLooterAmmoDistance, &DefaultItemLooterSettings.ItemLooterAmmoDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterModsEnabled", &CustomItemLooterSettings.ItemLooterModsEnabled, &DefaultItemLooterSettings.ItemLooterModsEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterModsDistance", &CustomItemLooterSettings.ItemLooterModsDistance, &DefaultItemLooterSettings.ItemLooterModsDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterMagazinesEnabled", &CustomItemLooterSettings.ItemLooterMagazinesEnabled, &DefaultItemLooterSettings.ItemLooterMagazinesEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterMagazinesDistance", &CustomItemLooterSettings.ItemLooterMagazinesDistance, &DefaultItemLooterSettings.ItemLooterMagazinesDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterBobbleheadsEnabled", &CustomItemLooterSettings.ItemLooterBobbleheadsEnabled, &DefaultItemLooterSettings.ItemLooterBobbleheadsEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterBobbleheadsDistance", &CustomItemLooterSettings.ItemLooterBobbleheadsDistance, &DefaultItemLooterSettings.ItemLooterBobbleheadsDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterAidEnabled", &CustomItemLooterSettings.ItemLooterAidEnabled, &DefaultItemLooterSettings.ItemLooterAidEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterAidDistance", &CustomItemLooterSettings.ItemLooterAidDistance, &DefaultItemLooterSettings.ItemLooterAidDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterKnownPlansEnabled", &CustomItemLooterSettings.ItemLooterKnownPlansEnabled, &DefaultItemLooterSettings.ItemLooterKnownPlansEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterKnownPlansDistance", &CustomItemLooterSettings.ItemLooterKnownPlansDistance, &DefaultItemLooterSettings.ItemLooterKnownPlansDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterUnknownPlansEnabled", &CustomItemLooterSettings.ItemLooterUnknownPlansEnabled, &DefaultItemLooterSettings.ItemLooterUnknownPlansEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterUnknownPlansDistance", &CustomItemLooterSettings.ItemLooterUnknownPlansDistance, &DefaultItemLooterSettings.ItemLooterUnknownPlansDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterMiscEnabled", &CustomItemLooterSettings.ItemLooterMiscEnabled, &DefaultItemLooterSettings.ItemLooterMiscEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterMiscDistance", &CustomItemLooterSettings.ItemLooterMiscDistance, &DefaultItemLooterSettings.ItemLooterMiscDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterUnlistedEnabled", &CustomItemLooterSettings.ItemLooterUnlistedEnabled, &DefaultItemLooterSettings.ItemLooterUnlistedEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterUnlistedDistance", &CustomItemLooterSettings.ItemLooterUnlistedDistance, &DefaultItemLooterSettings.ItemLooterUnlistedDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterListEnabled", &CustomItemLooterSettings.ItemLooterListEnabled, &DefaultItemLooterSettings.ItemLooterListEnabled);
	GetSliderInt("ItemLooterSettings", "ItemLooterListDistance", &CustomItemLooterSettings.ItemLooterListDistance, &DefaultItemLooterSettings.ItemLooterListDistance, 0, 3000);
	GetBool("ItemLooterSettings", "ItemLooterBlacklistToggle", &CustomItemLooterSettings.ItemLooterBlacklistToggle, &DefaultItemLooterSettings.ItemLooterBlacklistToggle);
	for (int i = 0; i < 100; i++)
	{
		char ItemEnabledText[sizeof("ItemLooterEnabled99")];
		char ItemFormidText[sizeof("ItemLooterList99")];
		sprintf_s(ItemEnabledText, "ItemLooterEnabled%d", i);
		sprintf_s(ItemFormidText, "ItemLooterList%d", i);
		GetBool("ItemLooterSettings", ItemEnabledText, &CustomItemLooterSettings.ItemLooterEnabledList[i], &DefaultItemLooterSettings.ItemLooterEnabledList[i]);
		GetDWORD("ItemLooterSettings", ItemFormidText, &CustomItemLooterSettings.ItemLooterFormidList[i], &DefaultItemLooterSettings.ItemLooterFormidList[i]);
	}
	for (int i = 0; i < 64; i++)
	{
		char ItemBlacklistEnabledText[sizeof("ItemLooterBlacklistEnabled63")];
		char ItemBlacklistFormidText[sizeof("ItemLooterBlacklist63")];
		sprintf_s(ItemBlacklistEnabledText, "ItemLooterBlacklistEnabled%d", i);
		sprintf_s(ItemBlacklistFormidText, "ItemLooterBlacklist%d", i);
		GetBool("ItemLooterSettings", ItemBlacklistEnabledText, &CustomItemLooterSettings.ItemLooterBlacklistEnabled[i], &DefaultItemLooterSettings.ItemLooterBlacklistEnabled[i]);
		GetDWORD("ItemLooterSettings", ItemBlacklistFormidText, &CustomItemLooterSettings.ItemLooterBlacklist[i], &DefaultItemLooterSettings.ItemLooterBlacklist[i]);
	}
	if (CustomItemLooterSettings.ItemAutomaticSpeedMax < CustomItemLooterSettings.ItemAutomaticSpeedMin)
	{
		CustomItemLooterSettings.ItemAutomaticSpeedMax = CustomItemLooterSettings.ItemAutomaticSpeedMin;
	}
}

void SetItemLooterSettings()
{
	if (CustomItemLooterSettings.ItemAutomaticSpeedMax < CustomItemLooterSettings.ItemAutomaticSpeedMin)
	{
		CustomItemLooterSettings.ItemAutomaticSpeedMax = CustomItemLooterSettings.ItemAutomaticSpeedMin;
	}
	SetBool("ItemLooterSettings", "ItemKeybindEnabled", &CustomItemLooterSettings.ItemKeybindEnabled, &DefaultItemLooterSettings.ItemKeybindEnabled);
	SetBool("ItemLooterSettings", "ItemAutomaticLootingEnabled", &CustomItemLooterSettings.ItemAutomaticLootingEnabled, &DefaultItemLooterSettings.ItemAutomaticLootingEnabled);
	SetBool("ItemLooterSettings", "ItemAutomaticStatus", &CustomItemLooterSettings.ItemAutomaticStatus, &DefaultItemLooterSettings.ItemAutomaticStatus);
	SetSliderInt("ItemLooterSettings", "ItemAutomaticSpeedMin", &CustomItemLooterSettings.ItemAutomaticSpeedMin, &DefaultItemLooterSettings.ItemAutomaticSpeedMin, 10, 60);
	SetSliderInt("ItemLooterSettings", "ItemAutomaticSpeedMax", &CustomItemLooterSettings.ItemAutomaticSpeedMax, &DefaultItemLooterSettings.ItemAutomaticSpeedMax, 10, 60);
	SetBool("ItemLooterSettings", "ItemLooterWeaponsEnabled", &CustomItemLooterSettings.ItemLooterWeaponsEnabled, &DefaultItemLooterSettings.ItemLooterWeaponsEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterWeaponsDistance", &CustomItemLooterSettings.ItemLooterWeaponsDistance, &DefaultItemLooterSettings.ItemLooterWeaponsDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterArmorEnabled", &CustomItemLooterSettings.ItemLooterArmorEnabled, &DefaultItemLooterSettings.ItemLooterArmorEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterArmorDistance", &CustomItemLooterSettings.ItemLooterArmorDistance, &DefaultItemLooterSettings.ItemLooterArmorDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterAmmoEnabled", &CustomItemLooterSettings.ItemLooterAmmoEnabled, &DefaultItemLooterSettings.ItemLooterAmmoEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterAmmoDistance", &CustomItemLooterSettings.ItemLooterAmmoDistance, &DefaultItemLooterSettings.ItemLooterAmmoDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterModsEnabled", &CustomItemLooterSettings.ItemLooterModsEnabled, &DefaultItemLooterSettings.ItemLooterModsEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterModsDistance", &CustomItemLooterSettings.ItemLooterModsDistance, &DefaultItemLooterSettings.ItemLooterModsDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterMagazinesEnabled", &CustomItemLooterSettings.ItemLooterMagazinesEnabled, &DefaultItemLooterSettings.ItemLooterMagazinesEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterMagazinesDistance", &CustomItemLooterSettings.ItemLooterMagazinesDistance, &DefaultItemLooterSettings.ItemLooterMagazinesDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterBobbleheadsEnabled", &CustomItemLooterSettings.ItemLooterBobbleheadsEnabled, &DefaultItemLooterSettings.ItemLooterBobbleheadsEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterBobbleheadsDistance", &CustomItemLooterSettings.ItemLooterBobbleheadsDistance, &DefaultItemLooterSettings.ItemLooterBobbleheadsDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterAidEnabled", &CustomItemLooterSettings.ItemLooterAidEnabled, &DefaultItemLooterSettings.ItemLooterAidEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterAidDistance", &CustomItemLooterSettings.ItemLooterAidDistance, &DefaultItemLooterSettings.ItemLooterAidDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterKnownPlansEnabled", &CustomItemLooterSettings.ItemLooterKnownPlansEnabled, &DefaultItemLooterSettings.ItemLooterKnownPlansEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterKnownPlansDistance", &CustomItemLooterSettings.ItemLooterKnownPlansDistance, &DefaultItemLooterSettings.ItemLooterKnownPlansDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterUnknownPlansEnabled", &CustomItemLooterSettings.ItemLooterUnknownPlansEnabled, &DefaultItemLooterSettings.ItemLooterUnknownPlansEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterUnknownPlansDistance", &CustomItemLooterSettings.ItemLooterUnknownPlansDistance, &DefaultItemLooterSettings.ItemLooterUnknownPlansDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterMiscEnabled", &CustomItemLooterSettings.ItemLooterMiscEnabled, &DefaultItemLooterSettings.ItemLooterMiscEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterMiscDistance", &CustomItemLooterSettings.ItemLooterMiscDistance, &DefaultItemLooterSettings.ItemLooterMiscDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterUnlistedEnabled", &CustomItemLooterSettings.ItemLooterUnlistedEnabled, &DefaultItemLooterSettings.ItemLooterUnlistedEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterUnlistedDistance", &CustomItemLooterSettings.ItemLooterUnlistedDistance, &DefaultItemLooterSettings.ItemLooterUnlistedDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterListEnabled", &CustomItemLooterSettings.ItemLooterListEnabled, &DefaultItemLooterSettings.ItemLooterListEnabled);
	SetSliderInt("ItemLooterSettings", "ItemLooterListDistance", &CustomItemLooterSettings.ItemLooterListDistance, &DefaultItemLooterSettings.ItemLooterListDistance, 0, 3000);
	SetBool("ItemLooterSettings", "ItemLooterBlacklistToggle", &CustomItemLooterSettings.ItemLooterBlacklistToggle, &DefaultItemLooterSettings.ItemLooterBlacklistToggle);
	for (int i = 0; i < 100; i++)
	{
		char ItemEnabledText[sizeof("ItemLooterEnabled99")];
		char ItemFormidText[sizeof("ItemLooterList99")];
		sprintf_s(ItemEnabledText, "ItemLooterEnabled%d", i);
		sprintf_s(ItemFormidText, "ItemLooterList%d", i);
		SetBool("ItemLooterSettings", ItemEnabledText, &CustomItemLooterSettings.ItemLooterEnabledList[i], &DefaultItemLooterSettings.ItemLooterEnabledList[i]);
		SetDWORD("ItemLooterSettings", ItemFormidText, &CustomItemLooterSettings.ItemLooterFormidList[i], &DefaultItemLooterSettings.ItemLooterFormidList[i]);
	}
	for (int i = 0; i < 64; i++)
	{
		char ItemBlacklistEnabledText[sizeof("ItemLooterBlacklistEnabled63")];
		char ItemBlacklistFormidText[sizeof("ItemLooterBlacklist63")];
		sprintf_s(ItemBlacklistEnabledText, "ItemLooterBlacklistEnabled%d", i);
		sprintf_s(ItemBlacklistFormidText, "ItemLooterBlacklist%d", i);
		SetBool("ItemLooterSettings", ItemBlacklistEnabledText, &CustomItemLooterSettings.ItemLooterBlacklistEnabled[i], &DefaultItemLooterSettings.ItemLooterBlacklistEnabled[i]);
		SetDWORD("ItemLooterSettings", ItemBlacklistFormidText, &CustomItemLooterSettings.ItemLooterBlacklist[i], &DefaultItemLooterSettings.ItemLooterBlacklist[i]);
	}
}

void GetWeaponSettings()
{
	GetBool("WeaponSettings", "WeaponNoRecoil", &CustomWeaponSettings.NoRecoil, &DefaultWeaponSettings.NoRecoil);
	GetBool("WeaponSettings", "WeaponNoSpread", &CustomWeaponSettings.NoSpread, &DefaultWeaponSettings.NoSpread);
	GetBool("WeaponSettings", "WeaponNoSway", &CustomWeaponSettings.NoSway, &DefaultWeaponSettings.NoSway);
	GetBool("WeaponSettings", "WeaponInfiniteAmmo", &CustomWeaponSettings.InfiniteAmmo, &DefaultWeaponSettings.InfiniteAmmo);
	GetBool("WeaponSettings", "WeaponInstantReload", &CustomWeaponSettings.InstantReload, &DefaultWeaponSettings.InstantReload);
	GetBool("WeaponSettings", "WeaponAutomaticflag", &CustomWeaponSettings.Automaticflag, &DefaultWeaponSettings.Automaticflag);
	GetBool("WeaponSettings", "WeaponCapacityEnabled", &CustomWeaponSettings.CapacityEnabled, &DefaultWeaponSettings.CapacityEnabled);
	GetSliderInt("WeaponSettings", "WeaponCapacity", &CustomWeaponSettings.Capacity, &DefaultWeaponSettings.Capacity, 0, 999);
	GetBool("WeaponSettings", "WeaponSpeedEnabled", &CustomWeaponSettings.SpeedEnabled, &DefaultWeaponSettings.SpeedEnabled);
	GetSliderFloat("WeaponSettings", "WeaponSpeed", &CustomWeaponSettings.Speed, &DefaultWeaponSettings.Speed, 0.0f, 100.0f);
	GetBool("WeaponSettings", "WeaponReachEnabled", &CustomWeaponSettings.ReachEnabled, &DefaultWeaponSettings.ReachEnabled);
	GetSliderFloat("WeaponSettings", "WeaponReach", &CustomWeaponSettings.Reach, &DefaultWeaponSettings.Reach, 0.0f, 999.0f);
}

void SetWeaponSettings()
{
	SetBool("WeaponSettings", "WeaponNoRecoil", &CustomWeaponSettings.NoRecoil, &DefaultWeaponSettings.NoRecoil);
	SetBool("WeaponSettings", "WeaponNoSpread", &CustomWeaponSettings.NoSpread, &DefaultWeaponSettings.NoSpread);
	SetBool("WeaponSettings", "WeaponNoSway", &CustomWeaponSettings.NoSway, &DefaultWeaponSettings.NoSway);
	SetBool("WeaponSettings", "WeaponInfiniteAmmo", &CustomWeaponSettings.InfiniteAmmo, &DefaultWeaponSettings.InfiniteAmmo);
	SetBool("WeaponSettings", "WeaponInstantReload", &CustomWeaponSettings.InstantReload, &DefaultWeaponSettings.InstantReload);
	SetBool("WeaponSettings", "WeaponAutomaticflag", &CustomWeaponSettings.Automaticflag, &DefaultWeaponSettings.Automaticflag);
	SetBool("WeaponSettings", "WeaponCapacityEnabled", &CustomWeaponSettings.CapacityEnabled, &DefaultWeaponSettings.CapacityEnabled);
	SetSliderInt("WeaponSettings", "WeaponCapacity", &CustomWeaponSettings.Capacity, &DefaultWeaponSettings.Capacity, 0, 999);
	SetBool("WeaponSettings", "WeaponSpeedEnabled", &CustomWeaponSettings.SpeedEnabled, &DefaultWeaponSettings.SpeedEnabled);
	SetSliderFloat("WeaponSettings", "WeaponSpeed", &CustomWeaponSettings.Speed, &DefaultWeaponSettings.Speed, 0.0f, 100.0f);
	SetBool("WeaponSettings", "WeaponReachEnabled", &CustomWeaponSettings.ReachEnabled, &DefaultWeaponSettings.ReachEnabled);
	SetSliderFloat("WeaponSettings", "WeaponReach", &CustomWeaponSettings.Reach, &DefaultWeaponSettings.Reach, 0.0f, 999.0f);
}

void GetTargetSettings()
{
	GetBool("TargetSettings", "LockPlayers", &CustomTargetSettings.LockPlayers, &DefaultTargetSettings.LockPlayers);
	GetBool("TargetSettings", "LockNPCs", &CustomTargetSettings.LockNPCs, &DefaultTargetSettings.LockNPCs);
	GetBool("TargetSettings", "IndirectPlayers", &CustomTargetSettings.IndirectPlayers, &DefaultTargetSettings.IndirectPlayers);
	GetBool("TargetSettings", "IndirectNPCs", &CustomTargetSettings.IndirectNPCs, &DefaultTargetSettings.IndirectNPCs);
	GetBool("TargetSettings", "DirectPlayers", &CustomTargetSettings.DirectPlayers, &DefaultTargetSettings.DirectPlayers);
	GetBool("TargetSettings", "DirectNPCs", &CustomTargetSettings.DirectNPCs, &DefaultTargetSettings.DirectNPCs);
	GetBool("TargetSettings", "TargetLiving", &CustomTargetSettings.TargetLiving, &DefaultTargetSettings.TargetLiving);
	GetBool("TargetSettings", "TargetDowned", &CustomTargetSettings.TargetDowned, &DefaultTargetSettings.TargetDowned);
	GetBool("TargetSettings", "TargetDead", &CustomTargetSettings.TargetDead, &DefaultTargetSettings.TargetDead);
	GetBool("TargetSettings", "TargetUnknown", &CustomTargetSettings.TargetUnknown, &DefaultTargetSettings.TargetUnknown);
	GetBool("TargetSettings", "IgnoreRenderDistance", &CustomTargetSettings.IgnoreRenderDistance, &DefaultTargetSettings.IgnoreRenderDistance);
	GetSliderFloat("TargetSettings", "LockingFOV", &CustomTargetSettings.LockingFOV, &DefaultTargetSettings.LockingFOV, 5.0f, 40.0f);
	GetBool("TargetSettings", "IgnoreEssentialNPCs", &CustomTargetSettings.IgnoreEssentialNPCs, &DefaultTargetSettings.IgnoreEssentialNPCs);
	GetRGB("TargetSettings", "LockingColor", CustomTargetSettings.LockingColor, DefaultTargetSettings.LockingColor);
	GetBool("TargetSettings", "Retargeting", &CustomTargetSettings.Retargeting, &DefaultTargetSettings.Retargeting);
	GetSliderInt("TargetSettings", "Cooldown", &CustomTargetSettings.Cooldown, &DefaultTargetSettings.Cooldown, 0, 120);
	GetSliderInt("TargetSettings", "SendDamageMin", &CustomTargetSettings.SendDamageMin, &DefaultTargetSettings.SendDamageMin, 1, 60);
	GetSliderInt("TargetSettings", "SendDamageMax", &CustomTargetSettings.SendDamageMax, &DefaultTargetSettings.SendDamageMax, 1, 60);
	GetSliderInt("TargetSettings", "FavoriteIndex", &CustomTargetSettings.FavoriteIndex, &DefaultTargetSettings.FavoriteIndex, 0, 12);
	if (CustomTargetSettings.SendDamageMax < CustomTargetSettings.SendDamageMin)
	{
		CustomTargetSettings.SendDamageMax = CustomTargetSettings.SendDamageMin;
	}
}

void SetTargetSettings()
{
	if (CustomTargetSettings.SendDamageMax < CustomTargetSettings.SendDamageMin)
	{
		CustomTargetSettings.SendDamageMax = CustomTargetSettings.SendDamageMin;
	}
	SetBool("TargetSettings", "LockPlayers", &CustomTargetSettings.LockPlayers, &DefaultTargetSettings.LockPlayers);
	SetBool("TargetSettings", "LockNPCs", &CustomTargetSettings.LockNPCs, &DefaultTargetSettings.LockNPCs);
	SetBool("TargetSettings", "IndirectPlayers", &CustomTargetSettings.IndirectPlayers, &DefaultTargetSettings.IndirectPlayers);
	SetBool("TargetSettings", "IndirectNPCs", &CustomTargetSettings.IndirectNPCs, &DefaultTargetSettings.IndirectNPCs);
	SetBool("TargetSettings", "DirectPlayers", &CustomTargetSettings.DirectPlayers, &DefaultTargetSettings.DirectPlayers);
	SetBool("TargetSettings", "DirectNPCs", &CustomTargetSettings.DirectNPCs, &DefaultTargetSettings.DirectNPCs);
	SetBool("TargetSettings", "TargetLiving", &CustomTargetSettings.TargetLiving, &DefaultTargetSettings.TargetLiving);
	SetBool("TargetSettings", "TargetDowned", &CustomTargetSettings.TargetDowned, &DefaultTargetSettings.TargetDowned);
	SetBool("TargetSettings", "TargetDead", &CustomTargetSettings.TargetDead, &DefaultTargetSettings.TargetDead);
	SetBool("TargetSettings", "TargetUnknown", &CustomTargetSettings.TargetUnknown, &DefaultTargetSettings.TargetUnknown);
	SetBool("TargetSettings", "IgnoreRenderDistance", &CustomTargetSettings.IgnoreRenderDistance, &DefaultTargetSettings.IgnoreRenderDistance);
	SetSliderFloat("TargetSettings", "LockingFOV", &CustomTargetSettings.LockingFOV, &DefaultTargetSettings.LockingFOV, 5.0f, 40.0f);
	SetBool("TargetSettings", "IgnoreEssentialNPCs", &CustomTargetSettings.IgnoreEssentialNPCs, &DefaultTargetSettings.IgnoreEssentialNPCs);
	SetRGB("TargetSettings", "LockingColor", CustomTargetSettings.LockingColor, DefaultTargetSettings.LockingColor);
	SetBool("TargetSettings", "Retargeting", &CustomTargetSettings.Retargeting, &DefaultTargetSettings.Retargeting);
	SetSliderInt("TargetSettings", "Cooldown", &CustomTargetSettings.Cooldown, &DefaultTargetSettings.Cooldown, 0, 120);
	SetSliderInt("TargetSettings", "SendDamageMin", &CustomTargetSettings.SendDamageMin, &DefaultTargetSettings.SendDamageMin, 1, 60);
	SetSliderInt("TargetSettings", "SendDamageMax", &CustomTargetSettings.SendDamageMax, &DefaultTargetSettings.SendDamageMax, 1, 60);
	SetSliderInt("TargetSettings", "FavoriteIndex", &CustomTargetSettings.FavoriteIndex, &DefaultTargetSettings.FavoriteIndex, 0, 12);
}

void GetLocalPlayerSettings()
{
	GetBool("LocalPlayerSettings", "PositionSpoofingEnabled", &CustomLocalPlayerSettings.PositionSpoofingEnabled, &DefaultLocalPlayerSettings.PositionSpoofingEnabled);
	GetBool("LocalPlayerSettings", "DrawPositionSpoofingEnabled", &CustomLocalPlayerSettings.DrawPositionSpoofingEnabled, &DefaultLocalPlayerSettings.DrawPositionSpoofingEnabled);
	GetSliderInt("LocalPlayerSettings", "PositionSpoofingHeight", &CustomLocalPlayerSettings.PositionSpoofingHeight, &DefaultLocalPlayerSettings.PositionSpoofingHeight, -524287, 524287);
	GetBool("LocalPlayerSettings", "NoclipEnabled", &CustomLocalPlayerSettings.NoclipEnabled, &DefaultLocalPlayerSettings.NoclipEnabled);
	GetSliderFloat("LocalPlayerSettings", "NoclipSpeed", &CustomLocalPlayerSettings.NoclipSpeed, &DefaultLocalPlayerSettings.NoclipSpeed, 0.0f, 2.0f);
	GetBool("LocalPlayerSettings", "ClientState", &CustomLocalPlayerSettings.ClientState, &DefaultLocalPlayerSettings.ClientState);
	GetBool("LocalPlayerSettings", "AutomaticClientState", &CustomLocalPlayerSettings.AutomaticClientState, &DefaultLocalPlayerSettings.AutomaticClientState);
	GetBool("LocalPlayerSettings", "FreezeApEnabled", &CustomLocalPlayerSettings.FreezeApEnabled, &DefaultLocalPlayerSettings.FreezeApEnabled);
	GetBool("LocalPlayerSettings", "ActionPointsEnabled", &CustomLocalPlayerSettings.ActionPointsEnabled, &DefaultLocalPlayerSettings.ActionPointsEnabled);
	GetSliderInt("LocalPlayerSettings", "ActionPoints", &CustomLocalPlayerSettings.ActionPoints, &DefaultLocalPlayerSettings.ActionPoints, 0, 99999);
	GetBool("LocalPlayerSettings", "StrengthEnabled", &CustomLocalPlayerSettings.StrengthEnabled, &DefaultLocalPlayerSettings.StrengthEnabled);
	GetSliderInt("LocalPlayerSettings", "Strength", &CustomLocalPlayerSettings.Strength, &DefaultLocalPlayerSettings.Strength, 0, 99999);
	GetBool("LocalPlayerSettings", "PerceptionEnabled", &CustomLocalPlayerSettings.PerceptionEnabled, &DefaultLocalPlayerSettings.PerceptionEnabled);
	GetSliderInt("LocalPlayerSettings", "Perception", &CustomLocalPlayerSettings.Perception, &DefaultLocalPlayerSettings.Perception, 0, 99999);
	GetBool("LocalPlayerSettings", "EnduranceEnabled", &CustomLocalPlayerSettings.EnduranceEnabled, &DefaultLocalPlayerSettings.EnduranceEnabled);
	GetSliderInt("LocalPlayerSettings", "Endurance", &CustomLocalPlayerSettings.Endurance, &DefaultLocalPlayerSettings.Endurance, 0, 99999);
	GetBool("LocalPlayerSettings", "CharismaEnabled", &CustomLocalPlayerSettings.CharismaEnabled, &DefaultLocalPlayerSettings.CharismaEnabled);
	GetSliderInt("LocalPlayerSettings", "Charisma", &CustomLocalPlayerSettings.Charisma, &DefaultLocalPlayerSettings.Charisma, 0, 99999);
	GetBool("LocalPlayerSettings", "IntelligenceEnabled", &CustomLocalPlayerSettings.IntelligenceEnabled, &DefaultLocalPlayerSettings.IntelligenceEnabled);
	GetSliderInt("LocalPlayerSettings", "Intelligence", &CustomLocalPlayerSettings.Intelligence, &DefaultLocalPlayerSettings.Intelligence, 0, 99999);
	GetBool("LocalPlayerSettings", "AgilityEnabled", &CustomLocalPlayerSettings.AgilityEnabled, &DefaultLocalPlayerSettings.AgilityEnabled);
	GetSliderInt("LocalPlayerSettings", "Agility", &CustomLocalPlayerSettings.Agility, &DefaultLocalPlayerSettings.Agility, 0, 99999);
	GetBool("LocalPlayerSettings", "LuckEnabled", &CustomLocalPlayerSettings.LuckEnabled, &DefaultLocalPlayerSettings.LuckEnabled);
	GetSliderInt("LocalPlayerSettings", "Luck", &CustomLocalPlayerSettings.Luck, &DefaultLocalPlayerSettings.Luck, 0, 99999);
}

void SetLocalPlayerSettings()
{
	SetBool("LocalPlayerSettings", "PositionSpoofingEnabled", &CustomLocalPlayerSettings.PositionSpoofingEnabled, &DefaultLocalPlayerSettings.PositionSpoofingEnabled);
	SetBool("LocalPlayerSettings", "DrawPositionSpoofingEnabled", &CustomLocalPlayerSettings.DrawPositionSpoofingEnabled, &DefaultLocalPlayerSettings.DrawPositionSpoofingEnabled);
	SetSliderInt("LocalPlayerSettings", "PositionSpoofingHeight", &CustomLocalPlayerSettings.PositionSpoofingHeight, &DefaultLocalPlayerSettings.PositionSpoofingHeight, -524287, 524287);
	SetBool("LocalPlayerSettings", "NoclipEnabled", &CustomLocalPlayerSettings.NoclipEnabled, &DefaultLocalPlayerSettings.NoclipEnabled);
	SetSliderFloat("LocalPlayerSettings", "NoclipSpeed", &CustomLocalPlayerSettings.NoclipSpeed, &DefaultLocalPlayerSettings.NoclipSpeed, 0.0f, 2.0f);
	SetBool("LocalPlayerSettings", "ClientState", &CustomLocalPlayerSettings.ClientState, &DefaultLocalPlayerSettings.ClientState);
	SetBool("LocalPlayerSettings", "AutomaticClientState", &CustomLocalPlayerSettings.AutomaticClientState, &DefaultLocalPlayerSettings.AutomaticClientState);
	SetBool("LocalPlayerSettings", "FreezeApEnabled", &CustomLocalPlayerSettings.FreezeApEnabled, &DefaultLocalPlayerSettings.FreezeApEnabled);
	SetBool("LocalPlayerSettings", "ActionPointsEnabled", &CustomLocalPlayerSettings.ActionPointsEnabled, &DefaultLocalPlayerSettings.ActionPointsEnabled);
	SetSliderInt("LocalPlayerSettings", "ActionPoints", &CustomLocalPlayerSettings.ActionPoints, &DefaultLocalPlayerSettings.ActionPoints, 0, 99999);
	SetBool("LocalPlayerSettings", "StrengthEnabled", &CustomLocalPlayerSettings.StrengthEnabled, &DefaultLocalPlayerSettings.StrengthEnabled);
	SetSliderInt("LocalPlayerSettings", "Strength", &CustomLocalPlayerSettings.Strength, &DefaultLocalPlayerSettings.Strength, 0, 99999);
	SetBool("LocalPlayerSettings", "PerceptionEnabled", &CustomLocalPlayerSettings.PerceptionEnabled, &DefaultLocalPlayerSettings.PerceptionEnabled);
	SetSliderInt("LocalPlayerSettings", "Perception", &CustomLocalPlayerSettings.Perception, &DefaultLocalPlayerSettings.Perception, 0, 99999);
	SetBool("LocalPlayerSettings", "EnduranceEnabled", &CustomLocalPlayerSettings.EnduranceEnabled, &DefaultLocalPlayerSettings.EnduranceEnabled);
	SetSliderInt("LocalPlayerSettings", "Endurance", &CustomLocalPlayerSettings.Endurance, &DefaultLocalPlayerSettings.Endurance, 0, 99999);
	SetBool("LocalPlayerSettings", "CharismaEnabled", &CustomLocalPlayerSettings.CharismaEnabled, &DefaultLocalPlayerSettings.CharismaEnabled);
	SetSliderInt("LocalPlayerSettings", "Charisma", &CustomLocalPlayerSettings.Charisma, &DefaultLocalPlayerSettings.Charisma, 0, 99999);
	SetBool("LocalPlayerSettings", "IntelligenceEnabled", &CustomLocalPlayerSettings.IntelligenceEnabled, &DefaultLocalPlayerSettings.IntelligenceEnabled);
	SetSliderInt("LocalPlayerSettings", "Intelligence", &CustomLocalPlayerSettings.Intelligence, &DefaultLocalPlayerSettings.Intelligence, 0, 99999);
	SetBool("LocalPlayerSettings", "AgilityEnabled", &CustomLocalPlayerSettings.AgilityEnabled, &DefaultLocalPlayerSettings.AgilityEnabled);
	SetSliderInt("LocalPlayerSettings", "Agility", &CustomLocalPlayerSettings.Agility, &DefaultLocalPlayerSettings.Agility, 0, 99999);
	SetBool("LocalPlayerSettings", "LuckEnabled", &CustomLocalPlayerSettings.LuckEnabled, &DefaultLocalPlayerSettings.LuckEnabled);
	SetSliderInt("LocalPlayerSettings", "Luck", &CustomLocalPlayerSettings.Luck, &DefaultLocalPlayerSettings.Luck, 0, 99999);
}

void GetOpkSettings()
{
	GetBool("OpkSettings", "OpkPlayersEnabled", &CustomOpkSettings.PlayersEnabled, &DefaultOpkSettings.PlayersEnabled);
	GetBool("OpkSettings", "OpkNpcsEnabled", &CustomOpkSettings.NpcsEnabled, &DefaultOpkSettings.NpcsEnabled);
}

void SetOpkSettings()
{
	SetBool("OpkSettings", "OpkPlayersEnabled", &CustomOpkSettings.PlayersEnabled, &DefaultOpkSettings.PlayersEnabled);
	SetBool("OpkSettings", "OpkNpcsEnabled", &CustomOpkSettings.NpcsEnabled, &DefaultOpkSettings.NpcsEnabled);
}

void GetUtilitySettings()
{
	GetBool("UtilitySettings", "DebugPlayer", &CustomUtilitySettings.DebugPlayer, &DefaultUtilitySettings.DebugPlayer);
	GetBool("UtilitySettings", "DebugEsp", &CustomUtilitySettings.DebugEsp, &DefaultUtilitySettings.DebugEsp);
	GetDWORD("UtilitySettings", "PtrFormid", &CustomUtilitySettings.PtrFormid, &DefaultUtilitySettings.PtrFormid);
	GetDWORD("UtilitySettings", "AddressFormid", &CustomUtilitySettings.AddressFormid, &DefaultUtilitySettings.AddressFormid);
}

void SetUtilitySettings()
{
	SetBool("UtilitySettings", "DebugPlayer", &CustomUtilitySettings.DebugPlayer, &DefaultUtilitySettings.DebugPlayer);
	SetBool("UtilitySettings", "DebugEsp", &CustomUtilitySettings.DebugEsp, &DefaultUtilitySettings.DebugEsp);
	SetDWORD("UtilitySettings", "PtrFormid", &CustomUtilitySettings.PtrFormid, &DefaultUtilitySettings.PtrFormid);
	SetDWORD("UtilitySettings", "AddressFormid", &CustomUtilitySettings.AddressFormid, &DefaultUtilitySettings.AddressFormid);
}

void GetSwapperSettings()
{
	GetDWORD("SwapperSettings", "SourceFormid", &CustomSwapperSettings.SourceFormid, &DefaultSwapperSettings.SourceFormid);
	GetDWORD("SwapperSettings", "DestinationFormid", &CustomSwapperSettings.DestinationFormid, &DefaultSwapperSettings.DestinationFormid);
}

void SetSwapperSettings()
{
	SetDWORD("SwapperSettings", "SourceFormid", &CustomSwapperSettings.SourceFormid, &DefaultSwapperSettings.SourceFormid);
	SetDWORD("SwapperSettings", "DestinationFormid", &CustomSwapperSettings.DestinationFormid, &DefaultSwapperSettings.DestinationFormid);
}

void GetTransferSettings()
{
	GetDWORD("TransferSettings", "SourceFormid", &CustomTransferSettings.SourceFormid, &DefaultTransferSettings.SourceFormid);
	GetDWORD("TransferSettings", "DestinationFormid", &CustomTransferSettings.DestinationFormid, &DefaultTransferSettings.DestinationFormid);
	GetBool("TransferSettings", "UseWhitelist", &CustomTransferSettings.UseWhitelist, &DefaultTransferSettings.UseWhitelist);
	GetBool("TransferSettings", "UseBlacklist", &CustomTransferSettings.UseBlacklist, &DefaultTransferSettings.UseBlacklist);
	for (int i = 0; i < 32; i++)
	{
		char WhitelistedText[sizeof("Whitelisted31")];
		char WhitelistText[sizeof("Whitelist31")];
		sprintf_s(WhitelistedText, "Whitelisted%d", i);
		sprintf_s(WhitelistText, "Whitelist%d", i);
		GetBool("TransferSettings", WhitelistedText, &CustomTransferSettings.Whitelisted[i], &DefaultTransferSettings.Whitelisted[i]);
		GetDWORD("TransferSettings", WhitelistText, &CustomTransferSettings.Whitelist[i], &DefaultTransferSettings.Whitelist[i]);
	}
	for (int i = 0; i < 32; i++)
	{
		char BlacklistedText[sizeof("Blacklisted31")];
		char BlacklistText[sizeof("Blacklist31")];
		sprintf_s(BlacklistedText, "Blacklisted%d", i);
		sprintf_s(BlacklistText, "Blacklist%d", i);
		GetBool("TransferSettings", BlacklistedText, &CustomTransferSettings.Blacklisted[i], &DefaultTransferSettings.Blacklisted[i]);
		GetDWORD("TransferSettings", BlacklistText, &CustomTransferSettings.Blacklist[i], &DefaultTransferSettings.Blacklist[i]);
	}
}

void SetTransferSettings()
{
	SetDWORD("TransferSettings", "SourceFormid", &CustomTransferSettings.SourceFormid, &DefaultTransferSettings.SourceFormid);
	SetDWORD("TransferSettings", "DestinationFormid", &CustomTransferSettings.DestinationFormid, &DefaultTransferSettings.DestinationFormid);
	SetBool("TransferSettings", "UseWhitelist", &CustomTransferSettings.UseWhitelist, &DefaultTransferSettings.UseWhitelist);
	SetBool("TransferSettings", "UseBlacklist", &CustomTransferSettings.UseBlacklist, &DefaultTransferSettings.UseBlacklist);
	for (int i = 0; i < 32; i++)
	{
		char WhitelistedText[sizeof("Whitelisted31")];
		char WhitelistText[sizeof("Whitelist31")];
		sprintf_s(WhitelistedText, "Whitelisted%d", i);
		sprintf_s(WhitelistText, "Whitelist%d", i);
		SetBool("TransferSettings", WhitelistedText, &CustomTransferSettings.Whitelisted[i], &DefaultTransferSettings.Whitelisted[i]);
		SetDWORD("TransferSettings", WhitelistText, &CustomTransferSettings.Whitelist[i], &DefaultTransferSettings.Whitelist[i]);
	}
	for (int i = 0; i < 32; i++)
	{
		char BlacklistedText[sizeof("Blacklisted31")];
		char BlacklistText[sizeof("Blacklist31")];
		sprintf_s(BlacklistedText, "Blacklisted%d", i);
		sprintf_s(BlacklistText, "Blacklist%d", i);
		SetBool("TransferSettings", BlacklistedText, &CustomTransferSettings.Blacklisted[i], &DefaultTransferSettings.Blacklisted[i]);
		SetDWORD("TransferSettings", BlacklistText, &CustomTransferSettings.Blacklist[i], &DefaultTransferSettings.Blacklist[i]);
	}
}

void GetTeleportSettings()
{
	for (int i = 0; i < 16; i++)
	{
		char DestinationText[sizeof("Destination15")];
		char CellFormidText[sizeof("CellFormid15")];
		char DisableSavingText[sizeof("DisableSaving15")];
		sprintf_s(DestinationText, "Destination%d", i);
		sprintf_s(CellFormidText, "CellFormid%d", i);
		sprintf_s(DisableSavingText, "DisableSaving%d", i);
		GetQuadFloat("TeleportSettings", DestinationText, CustomTeleportSettings.TeleportEntryData[i].Destination, DefaultTeleportSettings.TeleportEntryData[i].Destination);
		GetDWORD("TeleportSettings", CellFormidText, &CustomTeleportSettings.TeleportEntryData[i].CellFormid, &DefaultTeleportSettings.TeleportEntryData[i].CellFormid);
		GetBool("TeleportSettings", DisableSavingText, &CustomTeleportSettings.TeleportEntryData[i].DisableSaving, &DefaultTeleportSettings.TeleportEntryData[i].DisableSaving);
	}
}

void SetTeleportSettings()
{
	for (int i = 0; i < 16; i++)
	{
		char DestinationText[sizeof("Destination15")];
		char CellFormidText[sizeof("CellFormid15")];
		char DisableSavingText[sizeof("DisableSaving15")];
		sprintf_s(DestinationText, "Destination%d", i);
		sprintf_s(CellFormidText, "CellFormid%d", i);
		sprintf_s(DisableSavingText, "DisableSaving%d", i);
		SetQuadFloat("TeleportSettings", DestinationText, CustomTeleportSettings.TeleportEntryData[i].Destination, DefaultTeleportSettings.TeleportEntryData[i].Destination);
		SetDWORD("TeleportSettings", CellFormidText, &CustomTeleportSettings.TeleportEntryData[i].CellFormid, &DefaultTeleportSettings.TeleportEntryData[i].CellFormid);
		SetBool("TeleportSettings", DisableSavingText, &CustomTeleportSettings.TeleportEntryData[i].DisableSaving, &DefaultTeleportSettings.TeleportEntryData[i].DisableSaving);
	}
}

void GetNukeCodeSettings()
{
	GetBool("NukeCodeSettings", "AutomaticNukeCodes", &CustomNukeCodeSettings.AutomaticNukeCodes, &DefaultNukeCodeSettings.AutomaticNukeCodes);
	GetBool("NukeCodeSettings", "DrawCodeAlpha", &CustomNukeCodeSettings.DrawCodeAlpha, &DefaultNukeCodeSettings.DrawCodeAlpha);
	GetBool("NukeCodeSettings", "DrawCodeBravo", &CustomNukeCodeSettings.DrawCodeBravo, &DefaultNukeCodeSettings.DrawCodeBravo);
	GetBool("NukeCodeSettings", "DrawCodeCharlie", &CustomNukeCodeSettings.DrawCodeCharlie, &DefaultNukeCodeSettings.DrawCodeCharlie);
}

void SetNukeCodeSettings()
{
	SetBool("NukeCodeSettings", "AutomaticNukeCodes", &CustomNukeCodeSettings.AutomaticNukeCodes, &DefaultNukeCodeSettings.AutomaticNukeCodes);
	SetBool("NukeCodeSettings", "DrawCodeAlpha", &CustomNukeCodeSettings.DrawCodeAlpha, &DefaultNukeCodeSettings.DrawCodeAlpha);
	SetBool("NukeCodeSettings", "DrawCodeBravo", &CustomNukeCodeSettings.DrawCodeBravo, &DefaultNukeCodeSettings.DrawCodeBravo);
	SetBool("NukeCodeSettings", "DrawCodeCharlie", &CustomNukeCodeSettings.DrawCodeCharlie, &DefaultNukeCodeSettings.DrawCodeCharlie);
}

void GetLegendarySettings()
{
	GetBool("LegendarySettings", "OverrideLivingOneStar", &CustomLegendarySettings.OverrideLivingOneStar, &DefaultLegendarySettings.OverrideLivingOneStar);
	GetRGB("LegendarySettings", "LivingOneStarColor", CustomLegendarySettings.LivingOneStarColor, DefaultLegendarySettings.LivingOneStarColor);
	GetBool("LegendarySettings", "OverrideDeadOneStar", &CustomLegendarySettings.OverrideDeadOneStar, &DefaultLegendarySettings.OverrideDeadOneStar);
	GetRGB("LegendarySettings", "DeadOneStarColor", CustomLegendarySettings.DeadOneStarColor, DefaultLegendarySettings.DeadOneStarColor);
	GetBool("LegendarySettings", "OverrideLivingTwoStar", &CustomLegendarySettings.OverrideLivingTwoStar, &DefaultLegendarySettings.OverrideLivingTwoStar);
	GetRGB("LegendarySettings", "LivingTwoStarColor", CustomLegendarySettings.LivingTwoStarColor, DefaultLegendarySettings.LivingTwoStarColor);
	GetBool("LegendarySettings", "OverrideDeadTwoStar", &CustomLegendarySettings.OverrideDeadTwoStar, &DefaultLegendarySettings.OverrideDeadTwoStar);
	GetRGB("LegendarySettings", "DeadTwoStarColor", CustomLegendarySettings.DeadTwoStarColor, DefaultLegendarySettings.DeadTwoStarColor);
	GetBool("LegendarySettings", "OverrideLivingThreeStar", &CustomLegendarySettings.OverrideLivingThreeStar, &DefaultLegendarySettings.OverrideLivingThreeStar);
	GetRGB("LegendarySettings", "LivingThreeStarColor", CustomLegendarySettings.LivingThreeStarColor, DefaultLegendarySettings.LivingThreeStarColor);
	GetBool("LegendarySettings", "OverrideDeadThreeStar", &CustomLegendarySettings.OverrideDeadThreeStar, &DefaultLegendarySettings.OverrideDeadThreeStar);
	GetRGB("LegendarySettings", "DeadThreeStarColor", CustomLegendarySettings.DeadThreeStarColor, DefaultLegendarySettings.DeadThreeStarColor);
}

void SetLegendarySettings()
{
	SetBool("LegendarySettings", "OverrideLivingOneStar", &CustomLegendarySettings.OverrideLivingOneStar, &DefaultLegendarySettings.OverrideLivingOneStar);
	SetRGB("LegendarySettings", "LivingOneStarColor", CustomLegendarySettings.LivingOneStarColor, DefaultLegendarySettings.LivingOneStarColor);
	SetBool("LegendarySettings", "OverrideDeadOneStar", &CustomLegendarySettings.OverrideDeadOneStar, &DefaultLegendarySettings.OverrideDeadOneStar);
	SetRGB("LegendarySettings", "DeadOneStarColor", CustomLegendarySettings.DeadOneStarColor, DefaultLegendarySettings.DeadOneStarColor);
	SetBool("LegendarySettings", "OverrideLivingTwoStar", &CustomLegendarySettings.OverrideLivingTwoStar, &DefaultLegendarySettings.OverrideLivingTwoStar);
	SetRGB("LegendarySettings", "LivingTwoStarColor", CustomLegendarySettings.LivingTwoStarColor, DefaultLegendarySettings.LivingTwoStarColor);
	SetBool("LegendarySettings", "OverrideDeadTwoStar", &CustomLegendarySettings.OverrideDeadTwoStar, &DefaultLegendarySettings.OverrideDeadTwoStar);
	SetRGB("LegendarySettings", "DeadTwoStarColor", CustomLegendarySettings.DeadTwoStarColor, DefaultLegendarySettings.DeadTwoStarColor);
	SetBool("LegendarySettings", "OverrideLivingThreeStar", &CustomLegendarySettings.OverrideLivingThreeStar, &DefaultLegendarySettings.OverrideLivingThreeStar);
	SetRGB("LegendarySettings", "LivingThreeStarColor", CustomLegendarySettings.LivingThreeStarColor, DefaultLegendarySettings.LivingThreeStarColor);
	SetBool("LegendarySettings", "OverrideDeadThreeStar", &CustomLegendarySettings.OverrideDeadThreeStar, &DefaultLegendarySettings.OverrideDeadThreeStar);
	SetRGB("LegendarySettings", "DeadThreeStarColor", CustomLegendarySettings.DeadThreeStarColor, DefaultLegendarySettings.DeadThreeStarColor);
}

void GetFluxSettings()
{
	GetBool("FluxSettings", "CrimsonFluxEnabled", &CustomFluxSettings.CrimsonFluxEnabled, &DefaultFluxSettings.CrimsonFluxEnabled);
	GetBool("FluxSettings", "CobaltFluxEnabled", &CustomFluxSettings.CobaltFluxEnabled, &DefaultFluxSettings.CobaltFluxEnabled);
	GetBool("FluxSettings", "YellowcakeFluxEnabled", &CustomFluxSettings.YellowcakeFluxEnabled, &DefaultFluxSettings.YellowcakeFluxEnabled);
	GetBool("FluxSettings", "FluorescentFluxEnabled", &CustomFluxSettings.FluorescentFluxEnabled, &DefaultFluxSettings.FluorescentFluxEnabled);
	GetBool("FluxSettings", "VioletFluxEnabled", &CustomFluxSettings.VioletFluxEnabled, &DefaultFluxSettings.VioletFluxEnabled);
}

void SetFluxSettings()
{
	SetBool("FluxSettings", "CrimsonFluxEnabled", &CustomFluxSettings.CrimsonFluxEnabled, &DefaultFluxSettings.CrimsonFluxEnabled);
	SetBool("FluxSettings", "CobaltFluxEnabled", &CustomFluxSettings.CobaltFluxEnabled, &DefaultFluxSettings.CobaltFluxEnabled);
	SetBool("FluxSettings", "YellowcakeFluxEnabled", &CustomFluxSettings.YellowcakeFluxEnabled, &DefaultFluxSettings.YellowcakeFluxEnabled);
	SetBool("FluxSettings", "FluorescentFluxEnabled", &CustomFluxSettings.FluorescentFluxEnabled, &DefaultFluxSettings.FluorescentFluxEnabled);
	SetBool("FluxSettings", "VioletFluxEnabled", &CustomFluxSettings.VioletFluxEnabled, &DefaultFluxSettings.VioletFluxEnabled);
}

void GetEntityLooterSettings(const char *Section, EntityLooterSettings* Value, EntityLooterSettings* Default)
{
	GetBool(Section, "EntityLooterEnabled", &Value->EntityLooterEnabled, &Default->EntityLooterEnabled);
	GetBool(Section, "EntityLooterStatusEnabled", &Value->EntityLooterStatusEnabled, &Default->EntityLooterStatusEnabled);
	GetBool(Section, "EntityLooterAllWeaponsEnabled", &Value->EntityLooterAllWeaponsEnabled, &Default->EntityLooterAllWeaponsEnabled);
	GetBool(Section, "EntityLooterAllArmorEnabled", &Value->EntityLooterAllArmorEnabled, &Default->EntityLooterAllArmorEnabled);
	GetBool(Section, "EntityLooterOneStarWeaponsEnabled", &Value->EntityLooterOneStarWeaponsEnabled, &Default->EntityLooterOneStarWeaponsEnabled);
	GetBool(Section, "EntityLooterOneStarArmorEnabled", &Value->EntityLooterOneStarArmorEnabled, &Default->EntityLooterOneStarArmorEnabled);
	GetBool(Section, "EntityLooterTwoStarWeaponsEnabled", &Value->EntityLooterTwoStarWeaponsEnabled, &Default->EntityLooterTwoStarWeaponsEnabled);
	GetBool(Section, "EntityLooterTwoStarArmorEnabled", &Value->EntityLooterTwoStarArmorEnabled, &Default->EntityLooterTwoStarArmorEnabled);
	GetBool(Section, "EntityLooterThreeStarWeaponsEnabled", &Value->EntityLooterThreeStarWeaponsEnabled, &Default->EntityLooterThreeStarWeaponsEnabled);
	GetBool(Section, "EntityLooterThreeStarArmorEnabled", &Value->EntityLooterThreeStarArmorEnabled, &Default->EntityLooterThreeStarArmorEnabled);
	GetBool(Section, "EntityLooterAmmoEnabled", &Value->EntityLooterAmmoEnabled, &Default->EntityLooterAmmoEnabled);
	GetBool(Section, "EntityLooterModsEnabled", &Value->EntityLooterModsEnabled, &Default->EntityLooterModsEnabled);
	GetBool(Section, "EntityLooterCapsEnabled", &Value->EntityLooterCapsEnabled, &Default->EntityLooterCapsEnabled);
	GetBool(Section, "EntityLooterJunkEnabled", &Value->EntityLooterJunkEnabled, &Default->EntityLooterJunkEnabled);
	GetBool(Section, "EntityLooterAidEnabled", &Value->EntityLooterAidEnabled, &Default->EntityLooterAidEnabled);
	GetBool(Section, "EntityLooterTreasureMapsEnabled", &Value->EntityLooterTreasureMapsEnabled, &Default->EntityLooterTreasureMapsEnabled);
	GetBool(Section, "EntityLooterKnownPlansEnabled", &Value->EntityLooterKnownPlansEnabled, &Default->EntityLooterKnownPlansEnabled);
	GetBool(Section, "EntityLooterUnknownPlansEnabled", &Value->EntityLooterUnknownPlansEnabled, &Default->EntityLooterUnknownPlansEnabled);
	GetBool(Section, "EntityLooterMiscEnabled", &Value->EntityLooterMiscEnabled, &Default->EntityLooterMiscEnabled);
	GetBool(Section, "EntityLooterUnlistedEnabled", &Value->EntityLooterUnlistedEnabled, &Default->EntityLooterUnlistedEnabled);
	GetBool(Section, "EntityLooterListEnabled", &Value->EntityLooterListEnabled, &Default->EntityLooterListEnabled);
	GetBool(Section, "EntityLooterBlacklistToggle", &Value->EntityLooterBlacklistToggle, &Default->EntityLooterBlacklistToggle);
	for (int i = 0; i < 100; i++)
	{
		char EntityEnabledText[sizeof("EntityLooterEnabled99")];
		char EntityFormidText[sizeof("EntityLooterList99")];
		sprintf_s(EntityEnabledText, "EntityLooterEnabled%d", i);
		sprintf_s(EntityFormidText, "EntityLooterList%d", i);
		GetBool(Section, EntityEnabledText, &Value->EntityLooterEnabledList[i], &Default->EntityLooterEnabledList[i]);
		GetDWORD(Section, EntityFormidText, &Value->EntityLooterFormidList[i], &Default->EntityLooterFormidList[i]);
	}
	for (int i = 0; i < 64; i++)
	{
		char EntityBlacklistEnabledText[sizeof("EntityLooterBlacklistEnabled63")];
		char EntityBlacklistFormidText[sizeof("EntityLooterBlacklist63")];
		sprintf_s(EntityBlacklistEnabledText, "EntityLooterBlacklistEnabled%d", i);
		sprintf_s(EntityBlacklistFormidText, "EntityLooterBlacklist%d", i);
		GetBool(Section, EntityBlacklistEnabledText, &Value->EntityLooterBlacklistEnabled[i], &Default->EntityLooterBlacklistEnabled[i]);
		GetDWORD(Section, EntityBlacklistFormidText, &Value->EntityLooterBlacklist[i], &Default->EntityLooterBlacklist[i]);
	}
}

void SetEntityLooterSettings(const char *Section, EntityLooterSettings* Value, EntityLooterSettings* Default)
{
	SetBool(Section, "EntityLooterEnabled", &Value->EntityLooterEnabled, &Default->EntityLooterEnabled);
	SetBool(Section, "EntityLooterStatusEnabled", &Value->EntityLooterStatusEnabled, &Default->EntityLooterStatusEnabled);
	SetBool(Section, "EntityLooterAllWeaponsEnabled", &Value->EntityLooterAllWeaponsEnabled, &Default->EntityLooterAllWeaponsEnabled);
	SetBool(Section, "EntityLooterAllArmorEnabled", &Value->EntityLooterAllArmorEnabled, &Default->EntityLooterAllArmorEnabled);
	SetBool(Section, "EntityLooterOneStarWeaponsEnabled", &Value->EntityLooterOneStarWeaponsEnabled, &Default->EntityLooterOneStarWeaponsEnabled);
	SetBool(Section, "EntityLooterOneStarArmorEnabled", &Value->EntityLooterOneStarArmorEnabled, &Default->EntityLooterOneStarArmorEnabled);
	SetBool(Section, "EntityLooterTwoStarWeaponsEnabled", &Value->EntityLooterTwoStarWeaponsEnabled, &Default->EntityLooterTwoStarWeaponsEnabled);
	SetBool(Section, "EntityLooterTwoStarArmorEnabled", &Value->EntityLooterTwoStarArmorEnabled, &Default->EntityLooterTwoStarArmorEnabled);
	SetBool(Section, "EntityLooterThreeStarWeaponsEnabled", &Value->EntityLooterThreeStarWeaponsEnabled, &Default->EntityLooterThreeStarWeaponsEnabled);
	SetBool(Section, "EntityLooterThreeStarArmorEnabled", &Value->EntityLooterThreeStarArmorEnabled, &Default->EntityLooterThreeStarArmorEnabled);
	SetBool(Section, "EntityLooterAmmoEnabled", &Value->EntityLooterAmmoEnabled, &Default->EntityLooterAmmoEnabled);
	SetBool(Section, "EntityLooterModsEnabled", &Value->EntityLooterModsEnabled, &Default->EntityLooterModsEnabled);
	SetBool(Section, "EntityLooterCapsEnabled", &Value->EntityLooterCapsEnabled, &Default->EntityLooterCapsEnabled);
	SetBool(Section, "EntityLooterJunkEnabled", &Value->EntityLooterJunkEnabled, &Default->EntityLooterJunkEnabled);
	SetBool(Section, "EntityLooterAidEnabled", &Value->EntityLooterAidEnabled, &Default->EntityLooterAidEnabled);
	SetBool(Section, "EntityLooterTreasureMapsEnabled", &Value->EntityLooterTreasureMapsEnabled, &Default->EntityLooterTreasureMapsEnabled);
	SetBool(Section, "EntityLooterKnownPlansEnabled", &Value->EntityLooterKnownPlansEnabled, &Default->EntityLooterKnownPlansEnabled);
	SetBool(Section, "EntityLooterUnknownPlansEnabled", &Value->EntityLooterUnknownPlansEnabled, &Default->EntityLooterUnknownPlansEnabled);
	SetBool(Section, "EntityLooterMiscEnabled", &Value->EntityLooterMiscEnabled, &Default->EntityLooterMiscEnabled);
	SetBool(Section, "EntityLooterUnlistedEnabled", &Value->EntityLooterUnlistedEnabled, &Default->EntityLooterUnlistedEnabled);
	SetBool(Section, "EntityLooterListEnabled", &Value->EntityLooterListEnabled, &Default->EntityLooterListEnabled);
	SetBool(Section, "EntityLooterBlacklistToggle", &Value->EntityLooterBlacklistToggle, &Default->EntityLooterBlacklistToggle);
	for (int i = 0; i < 100; i++)
	{
		char EntityEnabledText[sizeof("EntityLooterEnabled99")];
		char EntityFormidText[sizeof("EntityLooterList99")];
		sprintf_s(EntityEnabledText, "EntityLooterEnabled%d", i);
		sprintf_s(EntityFormidText, "EntityLooterList%d", i);
		SetBool(Section, EntityEnabledText, &Value->EntityLooterEnabledList[i], &Default->EntityLooterEnabledList[i]);
		SetDWORD(Section, EntityFormidText, &Value->EntityLooterFormidList[i], &Default->EntityLooterFormidList[i]);
	}
	for (int i = 0; i < 64; i++)
	{
		char EntityBlacklistEnabledText[sizeof("EntityLooterBlacklistEnabled63")];
		char EntityBlacklistFormidText[sizeof("EntityLooterBlacklist63")];
		sprintf_s(EntityBlacklistEnabledText, "EntityLooterBlacklistEnabled%d", i);
		sprintf_s(EntityBlacklistFormidText, "EntityLooterBlacklist%d", i);
		SetBool(Section, EntityBlacklistEnabledText, &Value->EntityLooterBlacklistEnabled[i], &Default->EntityLooterBlacklistEnabled[i]);
		SetDWORD(Section, EntityBlacklistFormidText, &Value->EntityLooterBlacklist[i], &Default->EntityLooterBlacklist[i]);
	}
}

void GetHarvesterSettings()
{
	GetBool("HarvesterSettings", "HarvesterEnabled", &CustomHarvesterSettings.HarvesterEnabled, &DefaultHarvesterSettings.HarvesterEnabled);
	GetBool("HarvesterSettings", "HarvesterStatusEnabled", &CustomHarvesterSettings.HarvesterStatusEnabled, &DefaultHarvesterSettings.HarvesterStatusEnabled);
	GetBool("HarvesterSettings", "HarvesterOverrideEnabled", &CustomHarvesterSettings.HarvesterOverrideEnabled, &DefaultHarvesterSettings.HarvesterOverrideEnabled);
	for (int i = 0; i < 69; i++)
	{
		char HarvesterEnabledText[sizeof("HarvesterEnabled68")];
		sprintf_s(HarvesterEnabledText, "HarvesterEnabled%d", i);
		GetBool("HarvesterSettings", HarvesterEnabledText, &CustomHarvesterSettings.HarvesterEnabledList[i], &DefaultHarvesterSettings.HarvesterEnabledList[i]);
	}
}

void SetHarvesterSettings()
{
	SetBool("HarvesterSettings", "HarvesterEnabled", &CustomHarvesterSettings.HarvesterEnabled, &DefaultHarvesterSettings.HarvesterEnabled);
	SetBool("HarvesterSettings", "HarvesterStatusEnabled", &CustomHarvesterSettings.HarvesterStatusEnabled, &DefaultHarvesterSettings.HarvesterStatusEnabled);
	SetBool("HarvesterSettings", "HarvesterOverrideEnabled", &CustomHarvesterSettings.HarvesterOverrideEnabled, &DefaultHarvesterSettings.HarvesterOverrideEnabled);
	for (int i = 0; i < 69; i++)
	{
		char HarvesterEnabledText[sizeof("HarvesterEnabled68")];
		sprintf_s(HarvesterEnabledText, "HarvesterEnabled%d", i);
		SetBool("HarvesterSettings", HarvesterEnabledText, &CustomHarvesterSettings.HarvesterEnabledList[i], &DefaultHarvesterSettings.HarvesterEnabledList[i]);
	}
}

void GetKnownRecipeSettings()
{
	GetBool("KnownRecipeSettings", "KnownRecipesEnabled", &CustomKnownRecipeSettings.KnownRecipesEnabled, &DefaultKnownRecipeSettings.KnownRecipesEnabled);
	GetBool("KnownRecipeSettings", "UnknownRecipesEnabled", &CustomKnownRecipeSettings.UnknownRecipesEnabled, &DefaultKnownRecipeSettings.UnknownRecipesEnabled);
}

void SetKnownRecipeSettings()
{
	SetBool("KnownRecipeSettings", "KnownRecipesEnabled", &CustomKnownRecipeSettings.KnownRecipesEnabled, &DefaultKnownRecipeSettings.KnownRecipesEnabled);
	SetBool("KnownRecipeSettings", "UnknownRecipesEnabled", &CustomKnownRecipeSettings.UnknownRecipesEnabled, &DefaultKnownRecipeSettings.UnknownRecipesEnabled);
}

void GetMeleeSettings()
{
	GetBool("MeleeSettings", "MeleeEnabled", &CustomMeleeSettings.MeleeEnabled, &DefaultMeleeSettings.MeleeEnabled);
	GetSliderInt("MeleeSettings", "MeleeSpeedMin", &CustomMeleeSettings.MeleeSpeedMin, &DefaultMeleeSettings.MeleeSpeedMin, 1, 60);
	GetSliderInt("MeleeSettings", "MeleeSpeedMax", &CustomMeleeSettings.MeleeSpeedMax, &DefaultMeleeSettings.MeleeSpeedMax, 1, 60);

	if (CustomMeleeSettings.MeleeSpeedMax < CustomMeleeSettings.MeleeSpeedMin)
	{
		CustomMeleeSettings.MeleeSpeedMax = CustomMeleeSettings.MeleeSpeedMin;
	}
}

void SetMeleeSettings()
{
	if (CustomMeleeSettings.MeleeSpeedMax < CustomMeleeSettings.MeleeSpeedMin)
	{
		CustomMeleeSettings.MeleeSpeedMax = CustomMeleeSettings.MeleeSpeedMin;
	}

	SetBool("MeleeSettings", "MeleeEnabled", &CustomMeleeSettings.MeleeEnabled, &DefaultMeleeSettings.MeleeEnabled);
	SetSliderInt("MeleeSettings", "MeleeSpeedMin", &CustomMeleeSettings.MeleeSpeedMin, &DefaultMeleeSettings.MeleeSpeedMin, 1, 60);
	SetSliderInt("MeleeSettings", "MeleeSpeedMax", &CustomMeleeSettings.MeleeSpeedMax, &DefaultMeleeSettings.MeleeSpeedMax, 1, 60);
}

void GetChargenSettings()
{
	GetBool("ChargenSettings", "ChargenEditingEnabled", &CustomChargenSettings.ChargenEditingEnabled, &DefaultChargenSettings.ChargenEditingEnabled);
	GetSliderFloat("ChargenSettings", "Thin", &CustomChargenSettings.Thin, &DefaultChargenSettings.Thin, 0.0f, 1.0f);
	GetSliderFloat("ChargenSettings", "Muscular", &CustomChargenSettings.Muscular, &DefaultChargenSettings.Muscular, 0.0f, 1.0f);
	GetSliderFloat("ChargenSettings", "Large", &CustomChargenSettings.Large, &DefaultChargenSettings.Large, 0.0f, 1.0f);
}

void SetChargenSettings()
{
	SetBool("ChargenSettings", "ChargenEditingEnabled", &CustomChargenSettings.ChargenEditingEnabled, &DefaultChargenSettings.ChargenEditingEnabled);
	SetSliderFloat("ChargenSettings", "Thin", &CustomChargenSettings.Thin, &DefaultChargenSettings.Thin, 0.0f, 1.0f);
	SetSliderFloat("ChargenSettings", "Muscular", &CustomChargenSettings.Muscular, &DefaultChargenSettings.Muscular, 0.0f, 1.0f);
	SetSliderFloat("ChargenSettings", "Large", &CustomChargenSettings.Large, &DefaultChargenSettings.Large, 0.0f, 1.0f);
}

void GetExtraNPCSettings()
{
	GetBool("ExtraNPCSettings", "HideSettlerFaction", &CustomExtraNPCSettings.HideSettlerFaction, &DefaultExtraNPCSettings.HideSettlerFaction);
	GetBool("ExtraNPCSettings", "HideCraterRaiderFaction", &CustomExtraNPCSettings.HideCraterRaiderFaction, &DefaultExtraNPCSettings.HideCraterRaiderFaction);
	GetBool("ExtraNPCSettings", "HideDieHardFaction", &CustomExtraNPCSettings.HideDieHardFaction, &DefaultExtraNPCSettings.HideDieHardFaction);
	GetBool("ExtraNPCSettings", "HideSecretServiceFaction", &CustomExtraNPCSettings.HideSecretServiceFaction, &DefaultExtraNPCSettings.HideSecretServiceFaction);
	GetBool("ExtraNPCSettings", "UseNPCBlacklist", &CustomExtraNPCSettings.UseNPCBlacklist, &DefaultExtraNPCSettings.UseNPCBlacklist);
	for (int i = 0; i < 64; i++)
	{
		char NPCBlacklistEnabledText[sizeof("NPCBlacklistEnabled63")];
		char NPCBlacklistFormidText[sizeof("NPCBlacklist63")];
		sprintf_s(NPCBlacklistEnabledText, "NPCBlacklistEnabled%d", i);
		sprintf_s(NPCBlacklistFormidText, "NPCBlacklist%d", i);
		GetBool("ExtraNPCSettings", NPCBlacklistEnabledText, &CustomExtraNPCSettings.NPCBlacklistEnabled[i], &DefaultExtraNPCSettings.NPCBlacklistEnabled[i]);
		GetDWORD("ExtraNPCSettings", NPCBlacklistFormidText, &CustomExtraNPCSettings.NPCBlacklist[i], &DefaultExtraNPCSettings.NPCBlacklist[i]);
	}
}

void SetExtraNPCSettings()
{
	SetBool("ExtraNPCSettings", "HideSettlerFaction", &CustomExtraNPCSettings.HideSettlerFaction, &DefaultExtraNPCSettings.HideSettlerFaction);
	SetBool("ExtraNPCSettings", "HideCraterRaiderFaction", &CustomExtraNPCSettings.HideCraterRaiderFaction, &DefaultExtraNPCSettings.HideCraterRaiderFaction);
	SetBool("ExtraNPCSettings", "HideDieHardFaction", &CustomExtraNPCSettings.HideDieHardFaction, &DefaultExtraNPCSettings.HideDieHardFaction);
	SetBool("ExtraNPCSettings", "HideSecretServiceFaction", &CustomExtraNPCSettings.HideSecretServiceFaction, &DefaultExtraNPCSettings.HideSecretServiceFaction);
	SetBool("ExtraNPCSettings", "UseNPCBlacklist", &CustomExtraNPCSettings.UseNPCBlacklist, &DefaultExtraNPCSettings.UseNPCBlacklist);
	for (int i = 0; i < 64; i++)
	{
		char NPCBlacklistEnabledText[sizeof("NPCBlacklistEnabled63")];
		char NPCBlacklistFormidText[sizeof("NPCBlacklist63")];
		sprintf_s(NPCBlacklistEnabledText, "NPCBlacklistEnabled%d", i);
		sprintf_s(NPCBlacklistFormidText, "NPCBlacklist%d", i);
		SetBool("ExtraNPCSettings", NPCBlacklistEnabledText, &CustomExtraNPCSettings.NPCBlacklistEnabled[i], &DefaultExtraNPCSettings.NPCBlacklistEnabled[i]);
		SetDWORD("ExtraNPCSettings", NPCBlacklistFormidText, &CustomExtraNPCSettings.NPCBlacklist[i], &DefaultExtraNPCSettings.NPCBlacklist[i]);
	}
}

void GetBitMsgWriterSettings()
{
	bool AllowMessagesDefault = false;
	GetBool("BitMsgWriter", "AllowMessages", &AllowMessages, &AllowMessagesDefault);
}

void SetBitMsgWriterSettings()
{
	bool AllowMessagesDefault = false;
	SetBool("BitMsgWriter", "AllowMessages", &AllowMessages, &AllowMessagesDefault);
}

void GetExperimentalSettings()
{
	bool ExperimentalOverlayFixDefault = false;
	GetBool("ExperimentalOverlayFix", "ExperimentalOverlayFix", &ExperimentalOverlayFix, &ExperimentalOverlayFixDefault);
}

void SetExperimentalSettings()
{
	bool ExperimentalOverlayFixDefault = false;
	SetBool("ExperimentalOverlayFix", "ExperimentalOverlayFix", &ExperimentalOverlayFix, &ExperimentalOverlayFixDefault);
}

void ReadIniSettings()
{
	file.read(ini);
	GetOverlaySettingsA("PlayerSettings", &PlayerSettings, &DefaultPlayerSettings);
	GetOverlaySettingsA("NpcSettings", &NpcSettings, &DefaultNpcSettings);
	GetLegendarySettings();
	GetExtraNPCSettings();
	GetOverlaySettingsB("ContainerSettings", &ContainerSettings, &DefaultOverlaySettingsB);
	GetOverlaySettingsB("JunkSettings", &JunkSettings, &DefaultOverlaySettingsB);
	GetOverlaySettingsB("PlanSettings", &PlanSettings, &DefaultOverlaySettingsB);
	GetKnownRecipeSettings();
	GetOverlaySettingsB("MagazineSettings", &MagazineSettings, &DefaultOverlaySettingsB);
	GetOverlaySettingsB("BobbleheadSettings", &BobbleheadSettings, &DefaultOverlaySettingsB);
	GetOverlaySettingsB("ItemSettings", &ItemSettings, &DefaultOverlaySettingsB);
	GetOverlaySettingsB("FloraSettings", &FloraSettings, &FloraSettings);
	GetFluxSettings();
	GetOverlaySettingsB("EntitySettings", &EntitySettings, &DefaultOverlaySettingsB);
	GetScrapSettings();
	GetItemLooterSettings();
	GetEntityLooterSettings("NPCLooterSettings", &NPCLooterSettings, &DefaultEntityLooterSettings);
	GetEntityLooterSettings("ContainerLooterSettings", &ContainerLooterSettings, &DefaultEntityLooterSettings);
	GetHarvesterSettings();
	GetWeaponSettings();
	GetTargetSettings();
	GetLocalPlayerSettings();
	GetOpkSettings();
	GetUtilitySettings();
	GetTransferSettings();
	GetTeleportSettings();
	GetNukeCodeSettings();
	GetMeleeSettings();
	GetChargenSettings();
	GetBitMsgWriterSettings();
	GetExperimentalSettings();
	file.write(ini, true);
}

void WriteIniSettings()
{
	file.read(ini);
	SetOverlaySettingsA("PlayerSettings", &PlayerSettings, &DefaultPlayerSettings);
	SetOverlaySettingsA("NpcSettings", &NpcSettings, &DefaultNpcSettings);
	SetLegendarySettings();
	SetExtraNPCSettings();
	SetOverlaySettingsB("ContainerSettings", &ContainerSettings, &DefaultOverlaySettingsB);
	SetOverlaySettingsB("JunkSettings", &JunkSettings, &DefaultOverlaySettingsB);
	SetOverlaySettingsB("PlanSettings", &PlanSettings, &DefaultOverlaySettingsB);
	SetKnownRecipeSettings();
	SetOverlaySettingsB("MagazineSettings", &MagazineSettings, &DefaultOverlaySettingsB);
	SetOverlaySettingsB("BobbleheadSettings", &BobbleheadSettings, &DefaultOverlaySettingsB);
	SetOverlaySettingsB("ItemSettings", &ItemSettings, &DefaultOverlaySettingsB);
	SetOverlaySettingsB("FloraSettings", &FloraSettings, &FloraSettings);
	SetFluxSettings();
	SetOverlaySettingsB("EntitySettings", &EntitySettings, &DefaultOverlaySettingsB);
	SetScrapSettings();
	SetItemLooterSettings();
	SetEntityLooterSettings("NPCLooterSettings", &NPCLooterSettings, &DefaultEntityLooterSettings);
	SetEntityLooterSettings("ContainerLooterSettings", &ContainerLooterSettings, &DefaultEntityLooterSettings);
	SetHarvesterSettings();
	SetWeaponSettings();
	SetTargetSettings();
	SetLocalPlayerSettings();
	SetOpkSettings();
	SetUtilitySettings();
	SetTransferSettings();
	SetTeleportSettings();
	SetNukeCodeSettings();
	SetMeleeSettings();
	SetChargenSettings();
	SetBitMsgWriterSettings();
	SetExperimentalSettings();
	file.write(ini, true);
}
