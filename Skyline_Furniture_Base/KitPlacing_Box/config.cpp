////////////////////////////////////////////////////////////////////
//DeRap: Skyline_Furniture_Base\KitPlacing_Box\config.bin
//Produced from mikero's Dos Tools Dll version 7.95
//https://mikero.bytex.digital/Downloads
//'now' is Mon May 11 04:21:58 2026 : 'file' last modified on Mon Aug 26 14:48:13 2019
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class Skyline_Furniture_Base_Kit
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Characters_Backpacks","DZ_Characters_Pants","DZ_Characters_Tops","DZ_Gear_Containers","DZ_Characters_Headgear","DZ_Gear_Camping","DZ_Gear_Crafting","DZ_Gear_Tools","DZ_Data"};
	};
};
class CfgMods
{
	class Skyline_Furniture_Base
	{
		dir = "Skyline_Furniture_Base";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Skyline_Furniture_Base";
		credits = "";
		author = "KeviinSkyline";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"Skyline_Furniture_Base\scripts\4_world"};
			};
		};
	};
};
class CfgVehicles
{
	class Container_Base;
	class WoodenCrate: Container_Base{};
	class Skyline_Kit_Gun_Cabinet: WoodenCrate
	{
		scope = 2;
		displayName = "Gun cabinet Kit";
		descriptionShort = "Furniture can be disassembled with a screwdriver";
		model = "Skyline_Furniture_Base\KitPlacing_Box\Kit_Box.p3d";
		itemSize[] = {10,4};
		carveNavmesh = 1;
		canBeDigged = 0;
		simulation = "inventoryItem";
		physLayer = "item_small";
		SingleUseActions[] = {527};
		ContinuousActions[] = {231};
		rotationFlags = 2;
		InteractActions[] = {};
		weight = 280;
		itemBehaviour = 2;
		hiddenSelections[] = {"Camo"};
		hiddenSelectionsTextures[] = {"\Skyline_Furniture_Base\KitPlacing_Box\Textures\Kit_Box_GunCabinet_co.paa"};
		class Cargo{};
	};
	class Skyline_Kit_Gun_Rack: WoodenCrate
	{
		scope = 2;
		displayName = "Gun rack Kit";
		descriptionShort = "Furniture can be disassembled with a screwdriver";
		model = "Skyline_Furniture_Base\KitPlacing_Box\Kit_Box.p3d";
		itemSize[] = {8,8};
		carveNavmesh = 1;
		canBeDigged = 0;
		simulation = "inventoryItem";
		physLayer = "item_small";
		SingleUseActions[] = {527};
		ContinuousActions[] = {231};
		rotationFlags = 2;
		InteractActions[] = {};
		weight = 280;
		itemBehaviour = 2;
		hiddenSelections[] = {"Camo"};
		hiddenSelectionsTextures[] = {"\Skyline_Furniture_Base\KitPlacing_Box\Textures\Kit_Box_GunRack_co.paa"};
		class Cargo{};
	};
	class Skyline_Kit_Fridge: WoodenCrate
	{
		scope = 2;
		displayName = "Fridge Kit";
		descriptionShort = "Furniture can be disassembled with a screwdriver";
		model = "Skyline_Furniture_Base\KitPlacing_Box\Kit_Box.p3d";
		itemSize[] = {8,8};
		carveNavmesh = 1;
		canBeDigged = 0;
		simulation = "inventoryItem";
		physLayer = "item_small";
		SingleUseActions[] = {527};
		ContinuousActions[] = {231};
		rotationFlags = 2;
		InteractActions[] = {};
		weight = 280;
		itemBehaviour = 2;
		hiddenSelections[] = {"Camo"};
		hiddenSelectionsTextures[] = {"\Skyline_Furniture_Base\KitPlacing_Box\Textures\Kit_Box_Fridge_co.paa"};
		class Cargo{};
	};
	class Skyline_Kit_Shelf: WoodenCrate
	{
		scope = 2;
		displayName = "Shelf Kit";
		descriptionShort = "Furniture can be disassembled with a screwdriver";
		model = "Skyline_Furniture_Base\KitPlacing_Box\Kit_Box.p3d";
		itemSize[] = {10,5};
		carveNavmesh = 1;
		canBeDigged = 0;
		simulation = "inventoryItem";
		physLayer = "item_small";
		SingleUseActions[] = {527};
		ContinuousActions[] = {231};
		rotationFlags = 2;
		InteractActions[] = {};
		weight = 280;
		itemBehaviour = 2;
		hiddenSelections[] = {"Camo"};
		hiddenSelectionsTextures[] = {"\Skyline_Furniture_Base\KitPlacing_Box\Textures\Kit_Box_Shelf_co.paa"};
		class Cargo{};
	};
	class Skyline_Kit_StorageBox: WoodenCrate
	{
		scope = 2;
		displayName = "Storage Box Kit";
		descriptionShort = "Furniture can be disassembled with a screwdriver";
		model = "Skyline_Furniture_Base\KitPlacing_Box\Kit_Box.p3d";
		itemSize[] = {10,5};
		carveNavmesh = 1;
		canBeDigged = 0;
		simulation = "inventoryItem";
		physLayer = "item_small";
		SingleUseActions[] = {527};
		ContinuousActions[] = {231};
		rotationFlags = 2;
		InteractActions[] = {};
		weight = 280;
		itemBehaviour = 2;
		hiddenSelections[] = {"Camo"};
		hiddenSelectionsTextures[] = {"\Skyline_Furniture_Base\KitPlacing_Box\Textures\Kit_Box_StorageBox_co.paa"};
		class Cargo{};
	};
};
