
class CfgPatches
{
	class AloneZPackZB
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Weapons_Firearms", "DZ_Weapons_Melee", "DZ_Weapons_Explosives", "DZ_Characters", "DZ_Characters_Heads", "DZ_Characters_Zombies", "AI_Bandits"};
	};
	class AloneZPackZB_AI
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data", "DZ_data_aiconfigs", "DZ_AI"};
	};
};

class CfgMods
{
	class AloneZPackZB
	{
		dir = "AloneZPackZB";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "AloneZPackZB";
		credits = "AloneZ Team";
		author = "AloneZ";
		authorID = "";
		version = "2.0.0";
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"AloneZPackZB/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"AloneZPackZB/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"AloneZPackZB/scripts/5_Mission"};
			};
		};
	};
};

class AIParams
{
	class AgentTeams
	{
		TeamList[] += {"AloneZBots"};
		class AloneZBots
		{
			friends[] = {"AmbientLife"};
		};
	};
};

class GroupBehaviourTemplates
{
	class DZAloneZGroupBeh
	{
		type = "InfectedPack";
		alertDistributionSpeed = 20;
		catchUpTestDelay = 4;
		catchUpStartRadius = 80;
		catchUpTargetRadius = 7;
		groupRadius = 10;
		spawnMinDistanceBetweenAgents = 1;
		agentPathLength = 100;
		atNeedMinDuration = 60;
		atNeedMaxDuration = 120;
		singleAgentSafeKeeperDelayMin = 100;
		singleAgentSafeKeeperDelayMax = 100;
		preyAttractionRange = 350;
		innerOuterCircleRatio = 0.6;
		endAttractionRange = 300;
		attractionCooldown = 60;
		endAttractionTime = 300;
		targetEscapingSpeed = 1.5;
		killAddFear = 34;
		eatingTime = 600;
		huntingCooldown = 120;
		maxHuntingTime = 60;
		safeKeeperIntervalMin = 20;
		safeKeeperIntervalMax = 40;
		siegeAttackCountdownMin = 1;
		siegeAttackCountdownMax = 12;
		huntAttackCountdownMin = 1;
		huntAttackCountdownMax = 10;
		changeTargetCooldown = 5;
		changeTargetAlertRatio = 1.3;
		changeTargetEffectRadius = 6;
		subgroupSpacingMax = 500;
		enragedRingDistanceMax = 10;
		enragedRingDistanceMin = 3;
		enragedReachDistanceMin = 0.8;
		enragedReachDistanceMax = 3;
		enragedOnReachCount = 3;
		maxEnrageTime = 10;
		class LifeCycleDayTime
		{
			class Activity1
			{
				endTimeMin = 8.5;
				endTimeMax = 8.5;
				zoneType = "Rest";
			};
			class Activity2
			{
				endTimeMin = 16;
				endTimeMax = 16;
				zoneType = "HuntingGround";
				stayInZone = "false";
			};
			class Activity3
			{
				endTimeMin = 18.5;
				endTimeMax = 19.5;
				zoneType = "Rest";
			};
			class Activity4
			{
				endTimeMin = 22.5;
				endTimeMax = 23.5;
				zoneType = "HuntingGround";
				stayInZone = "false";
			};
		};
	};
};

class PathGraphFilters
{
	class AloneZBotOnHunt
	{
		class Flags
		{
			include[] = {"walk", "door", "inside", "jump", "climb", "jumpover"};
			exclude[] = {"disabled", "crawl", "crouch", "swim", "swimsea"};
		};
		class Costs
		{
			jump0 = 3;
			jump1 = 0;
			jump2 = 0;
			jump3 = 0;
			jump4 = 0;
			water = 5;
		};
	};
};

class CfgAIBehaviours
{
	class AloneZBot
	{
		name = "alonez_bots";
		HeadLookBoneName = "pin_lookat";
		teamName = "AloneZBots";
		defaultGroupTemplateName = "DZAloneZGroupBeh";
		class BehaviourHLInfectedPack
		{
			instantAlertRangeMin = 10;
			instantAlertRangeMax = 200;
			instantAlertStrength = 50;
			proximityAttackRange = 2.5;
			proximityAttackPredictTime = 0.5;
			attackCooldown = 2.5;
			attractionChangeTargetCooldown = 5;
			changeAttractionTargetRatio = 1.5;
			attractionNoiseStrengthTreshold = 3;
			attractionStrengthCeiling = 100;
			attractionStrengthDropSpeed = 5;
			attractionNoiseWindowStrengthTreshold = 20;
			attractionNoiseWindowSize = 5;
			attractionVisionPostponeTime = 3.5;
			class SlotCalm
			{
				class BehaviourCalm
				{
					travelingMode = "true";
					grazeOnSpotWeight = 0;
					grazeWalkingWeight = 0;
					restWeight = 0;
					travelWeight = 1;
					grazeOnSpotDurationMin = 5;
					grazeOnSpotDurationMax = 10;
					grazeWalkingDurationMin = 50;
					grazeWalkingDurationMax = 50;
					restingDurationMin = 0;
					restingDurationMax = 0;
					travelingDurationMin = 150;
					travelingDurationMax = 300;
					grazeWalkingSpeed = 1.2;
					travelingWalkingSpeed = 3.36;
					safetyDurationMin = 10;
					safetyDurationMax = 10;
					safetyLookAngleMin = 0.3;
					safetyLookAngleMax = 0.7;
					safetyLookAngleChangeInterval = 3;
					class GrazeMovement
					{
						maxSpeed = 4.25;
						minSpeed = 1;
						acceleration = 5;
						maxAngleSpeed = 180;
						slowRadius = 2;
						stopRadius = 1;
						pathFilter = "AloneZBotOnHunt";
					};
					class TravelingMovement
					{
						maxSpeed = 2.15;
						minSpeed = 1.78;
						acceleration = 5;
						maxAngleSpeed = 180;
						slowRadius = 2;
						stopRadius = 1;
						pathFilter = "AloneZBotOnHunt";
						slowToTurn = "true";
						smoothAcceleration = "true";
					};
					class CatchUpMovement
					{
						maxSpeed = 6.38;
						minSpeed = 1.78;
						acceleration = 5;
						maxAngleSpeed = 120;
						slowRadius = 2;
						stopRadius = 1;
						pathFilter = "AloneZBotOnHunt";
						slowToTurn = "true";
						smoothAcceleration = "true";
					};
				};
			};
			class SlotPreAttracted
			{
				class BehaviourInfectedPackInterested
				{
					class Movement
					{
						maxSpeed = 2.15;
						minSpeed = 1;
						acceleration = 5;
						maxAngleSpeed = 180;
						slowRadius = 2;
						stopRadius = 1;
						pathFilter = "AloneZBotOnHunt";
					};
				};
			};
			class SlotAttracted
			{
				class BehaviourInfectedPackSearching
				{
					class SoundsEntering
					{
						class Sound1{};
					};
					class SoundsDuring
					{
						class Sound1{};
						probability = 0.9;
						RepeatTimeMin = 2;
						RepeatTimeMax = 4;
						RepeatEnabled = 1;
					};
					attractionFollowupDistance = 120;
					noiseStrengthTreshold = 2.5;
					searchStateDurationMax = 20;
					cooldownStateDurationMin = 5;
					cooldownStateDurationMax = 15;
					class Movement
					{
						maxSpeed = 3.2;
						minSpeed = 2.2;
						acceleration = 0.5;
						maxAngleSpeed = 180;
						slowRadius = 4;
						stopRadius = 1;
						slowToTurn = 1;
						smoothAcceleration = 1;
						pathFilter = "AloneZBotOnHunt";
					};
				};
			};
			class SlotEnraged
			{
				class BehaviourInfectedPackEnraged
				{
					class SoundsEntering
					{
						class Sound1{};
					};
					class SoundsDuring
					{
						class Sound1{};
						probability = 0.9;
						RepeatTimeMin = 3;
						RepeatTimeMax = 6;
						RepeatEnabled = 1;
					};
					class Movement
					{
						maxSpeed = 4.4;
						minSpeed = 1.6;
						acceleration = 8;
						maxAngleSpeed = 180;
						slowRadius = 1.5;
						stopRadius = 0.8;
						slowToTurn = 1;
						smoothAcceleration = 1;
						pathFilter = "AloneZBotOnHunt";
					};
					class MovementApproaching
					{
						maxSpeed = 4.4;
						maxSpeedRange = 2.5;
						optimalSpeed = 1.6;
						minSpeed = 0.4;
						acceleration = 1.5;
						maxAngleSpeed = 120;
						slowRadius = 1;
						stopRadius = 0.2;
						slowToTurn = 1;
						smoothAcceleration = 1;
						pathFilter = "AloneZBotOnHunt";
					};
					class MovementReach
					{
						maxSpeed = 2.4;
						minSpeed = 1.1;
						acceleration = 2;
						maxAngleSpeed = 180;
						slowRadius = 1.6;
						stopRadius = 0.35;
						slowToTurn = 1;
						smoothAcceleration = 1;
						pathFilter = "AloneZBotOnHunt";
					};
				};
			};
			class SlotEnragedTargetLost
			{
				class BehaviourInfectedPackSearching
				{
					class SoundsDuring
					{
						class Sound1{};
						probability = 0.9;
						RepeatTimeMin = 3;
						RepeatTimeMax = 6;
						RepeatEnabled = 1;
					};
					class SoundsExiting
					{
						class Sound1{};
					};
					attractionFollowupDistance = 80;
					noiseStrengthTreshold = 4;
					searchStateDurationMax = 8;
					cooldownStateDurationMin = 4;
					cooldownStateDurationMax = 8;
					class Movement
					{
						maxSpeed = 2.2;
						minSpeed = 1.2;
						acceleration = 2.5;
						maxAngleSpeed = 180;
						slowRadius = 1;
						stopRadius = 0.2;
						slowToTurn = 1;
						smoothAcceleration = 1;
						pathFilter = "AloneZBotOnHunt";
					};
					class MovementAlerted
					{
						maxSpeed = 3.4;
						minSpeed = 1.2;
						acceleration = 4;
						maxAngleSpeed = 180;
						slowRadius = 1;
						stopRadius = 0.2;
						slowToTurn = 1;
						smoothAcceleration = 1;
						pathFilter = "AloneZBotOnHunt";
					};
				};
			};
			class AlertSystem
			{
				visionToAlertMultiplier = 15;
				noiseToAlertMultiplier = 8;
				damageToAlertMultiplier = 10000;
				noiseShotToAlertMultiplier = 3.5;
				class Calm
				{
					DropSpeed = 1;
					DropDelay = 0;
					MaxAlertValue = 20;
				};
				class Alerted
				{
					DropSpeed = 3;
					DropDelay = 20;
					MaxAlertValue = 100;
				};
				class AlertedExtra
				{
					dropSpeed = 4;
					dropDelay = 60;
					maxAlertValue = 200;
				};
			};
		};
		class NoiseSystemParams
		{
			rangeMin = 30;
			rangeMax = 150;
			rangeShotMin = 10;
			rangeShotMax = 350;
			radiusMin = 50;
			radiusMax = 125;
			radiusShotMin = 15;
			radiusShotMax = 270;
			shotVolExponent = 1;
			class NoiseStrengthTeamMultipliers
			{
				BigGame = 0.8;
				Zombies = 1;
				Player = 5;
			};
		};
		class TargetSystemDZBase
		{
			class VisionTeamMultipliers
			{
				BigGame = 0.8;
				Zombies = 1;
				Player = 5;
			};
			visionManSizeStand = 1;
			visionManSizeCrouch = 0.5;
			visionManSizeProne = 0.3;
			visionAngularSpeedMin = 0.1;
			visionAngularSpeedMax = 0.5;
			visionAngularSpeedMaxMult = 1.5;
			visionRangeMin = 20;
			visionRangeMax = 300;
			visionFov = 1.9;
			visionPeripheralRangeMin = 1;
			visionPeripheralRangeMax = 3;
			visionPeripheralFov = 3.15;
			visionNightMinMult = 1;
			visionNightMaxMult = 0.75;
			visionRainMinMult = 1;
			visionRainMaxMult = 0.9;
			visionFogMinMult = 1;
			visionFogMaxMult = 0.7;
			visionProximityRange = 2.5;
			visionProximityStrengthMult = 2;
			visionCloseRange = 10;
			visionCloseHeight = 1.8;
			visionCloseStrengthMult = 1.5;
		};
	};
};

class CfgSlots
{
	class Slot_AloneZHead
	{
		name = "AloneZHead";
		displayName = "";
		ghostIcon = "";
		show = "false";
	};
	class Slot_AloneZHands
	{
		name = "AloneZHands";
		displayName = "";
		ghostIcon = "set:dayz_inventory image:hands";
		boneName = "RightHand";
		show = "false";
	};
	class Slot_AloneZBody
	{
		name = "AloneZBody";
		displayName = "#STR_CfgBody0";
		ghostIcon = "set:dayz_inventory image:body";
		show = "false";
	};
	class Slot_AloneZLegs
	{
		name = "AloneZLegs";
		displayName = "#STR_CfgLegs0";
		ghostIcon = "set:dayz_inventory image:legs";
		show = "false";
	};
	class Slot_AloneZFeet
	{
		name = "AloneZFeet";
		displayName = "#STR_CfgFeet0";
		ghostIcon = "set:dayz_inventory image:feet";
		show = "false";
	};
};

class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyAloneZBody
	{
		scope = 2;
		model = "ai_bandits\models\proxy\BanditBody_DZ.p3d";
	};
	class ProxyAloneZFeet
	{
		scope = 2;
		model = "ai_bandits\models\proxy\BanditFeet_DZ.p3d";
	};
	class ProxyAloneZHands
	{
		scope = 2;
		model = "ai_bandits\models\proxy\BanditHands_DZ.p3d";
	};
	class ProxyAloneZHead
	{
		scope = 2;
		model = "ai_bandits\models\proxy\BanditHead_DZ.p3d";
	};
	class ProxyAloneZLegs
	{
		scope = 2;
		model = "ai_bandits\models\proxy\BanditLegs_DZ.p3d";
	};
};

class CfgVehicles
{
	class DayZInfected;
	class Clothing;
	class Inventory_Base;

	class AloneZ_BotBase: DayZInfected
	{
		scope = 0;
		faction = "dz_Civ_US";
		rarityUrban = -1;
		displayWeight = 0;
		simulation = "dayzinfected";
		class enfanimsys
		{
			meshObject = "ai_bandits\anims\bandit.xob";
			graphname = "ai_bandits\anims\animgraph\bandits.agr";
			defaultinstance = "ai_bandits\anims\animgraph\bandits.asi";
			startnode = "Master_SM";
			skeletonName = "bandit.xob";
		};
		class InputController
		{
			movementSpeedMapping[] = {0, 1.5, 2.9, 8.9};
			lookAtFilterTimeout = 0.5;
			lookAtFilterSpeed = 1.57;
		};
		accuracy = 0;
		threat[] = {1, 0.05, 0.05};
		displayName = "AloneZ Bot";
		descriptionShort = "AI Bot";
		vehicleClass = "Zombie";
		zombieLoot = "civilian";
		storageCategory = 3;
		hiddenSelections[] = {"camo"};
		htMin = 60;
		htMax = 1800;
		afMax = 30;
		mfMax = 0;
		mFact = 1;
		tBody = 37;
		selectionPersonality = "personality";
		faceType = "MaleWhiteHeadNew";
		launcherBone = "launcher";
		handGunBone = "RightHand";
		weaponBone = "weapon";
		selectionHeadWound = "injury_head";
		selectionBodyWound = "injury_body";
		selectionLArmWound = "injury_hands";
		selectionRArmWound = "injury_hands";
		selectionLLegWound = "injury_legs";
		selectionRLegWound = "injury_legs";
		memoryPointLStep = "footstepL";
		memoryPointRStep = "footstepR";
		memoryPointAim = "aimPoint";
		memoryPointCameraTarget = "camera";
		memoryPointCommonDamage = "l_femur_hit";
		memoryPointLeaningAxis = "leaning_axis";
		memoryPointAimingAxis = "aiming_axis";
		memoryPointHeadAxis = "head_axis";
		selectionLBrow = "lBrow";
		selectionMBrow = "mBrow";
		selectionRBrow = "rBrow";
		selectionLMouth = "lMouth";
		selectionMMouth = "mMouth";
		selectionRMouth = "rMouth";
		selectionEyelid = "Eyelids";
		selectionLip = "LLip";
		class P3DAttachments
		{
			P3DProxies[] = {"righthand"};
			BoneNames[] = {"righthand"};
		};
		class InventoryEquipment
		{
			playerSlots[] = {"Slot_AloneZHands"};
		};
		class Wounds
		{
			tex[] = {};
			mat[] = {"dz\characters\zombies\data\coveralls.rvmat", "dz\characters\zombies\data\coveralls_injury.rvmat", "dz\characters\zombies\data\coveralls_injury.rvmat"};
		};
		aiAgentTemplate = "AloneZBot";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1, {}}, {0.7, {}}, {0.5, {}}, {0.3, {}}, {0, {}}};
				};
			};
			class DamageZones
			{
				class Head
				{
					class Health
					{
						hitpoints = 30;
						transferToGlobalCoef = 1;
					};
					class ArmorType
					{
						class Projectile
						{
							class Health { damage = 1.5; };
						};
						class Melee
						{
							class Health { damage = 0.7; };
						};
						class FragGrenade
						{
							class Health { damage = 3; };
						};
					};
					componentNames[] = {"Head", "Neck"};
					fatalInjuryCoef = 0.1;
					inventorySlots[] = {"Headgear", "Mask"};
				};
				class Torso
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 1;
					};
					class ArmorType
					{
						class Melee
						{
							class Health { damage = 1.2; };
						};
						class FragGrenade
						{
							class Health { damage = 2; };
						};
					};
					componentNames[] = {"Spine1", "Spine3"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {"Vest", "Body", "Back"};
					inventorySlotsCoefs[] = {1, 1, 1};
				};
				class LeftArm: Torso
				{
					componentNames[] = {"LeftArm", "LeftForeArm"};
					fatalInjuryCoef = -1;
				};
				class RightArm: LeftArm
				{
					componentNames[] = {"RightArm", "RightForeArm"};
					fatalInjuryCoef = -1;
				};
				class LeftLeg
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 0.33;
					};
					class ArmorType
					{
						class FragGrenade
						{
							class Health { damage = 2; };
						};
					};
					componentNames[] = {"LeftLeg", "LeftUpLeg"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {"Legs"};
				};
				class RightLeg: LeftLeg
				{
					componentNames[] = {"RightLeg", "RightUpLeg"};
					fatalInjuryCoef = -1;
				};
				class LeftFoot
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 0.1;
					};
					class ArmorType
					{
						class FragGrenade
						{
							class Health { damage = 2; };
						};
					};
					transferToZonesNames[] = {"LeftLeg"};
					transferToZonesCoefs[] = {0.1};
					componentNames[] = {"LeftFoot"};
					fatalInjuryCoef = -1;
					inventorySlots[] = {"Feet"};
				};
				class RightFoot: LeftFoot
				{
					transferToZonesNames[] = {"RightLeg"};
					transferToZonesCoefs[] = {0.1};
					componentNames[] = {"RightFoot"};
					fatalInjuryCoef = -1;
				};
			};
		};
		class AnimEvents
		{
			class Steps {};
			class SoundVoice {};
			class Sounds {};
		};
	};

	class AloneZ_Bot_Concrete: AloneZ_BotBase
	{
		scope = 0;
		model = "ai_bandits\models\Bandit.p3d";
		attachments[] = {"AloneZBody", "AloneZLegs", "AloneZHands", "AloneZFeet", "Headgear", "Mask", "Eyewear", "LeftHand", "Gloves", "Armband", "Vest", "Body", "Back", "Hips", "Legs", "Feet"};
		hiddenSelections[] = {"beard", "hair", "personality"};
		class InventoryEquipment
		{
			playerSlots[] = {"Slot_Vest", "Slot_Body", "Slot_Hips", "Slot_Legs", "Slot_Back", "Slot_Headgear", "Slot_Mask", "Slot_Eyewear", "Slot_Gloves", "Slot_Feet", "Slot_Armband"};
		};
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[] = {"Headgear", "Mask", "Eyewear", "Gloves", "Armband", "Vest", "Body", "Back", "Hips", "Legs", "Feet"};
			};
		};
	};

	class AloneZ_Bot_MaleBase: AloneZ_Bot_Concrete
	{
		scope = 0;
		woman = 0;
		clothingType = "male";
	};
	class AloneZ_Bot_FemaleBase: AloneZ_Bot_Concrete
	{
		scope = 0;
		woman = 1;
		clothingType = "female";
	};

	class AloneZBody_Base: Clothing
	{
		scope = 1;
		displayName = "Bot Body";
		model = "ai_bandits\models\proxy\Cube_G.p3d";
		inventorySlot[] = {"AloneZBody"};
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"#(argb,8,8,3)color(0.843137,0.768627,0.658824,1.0,CO)"};
		class ClothingTypes
		{
			male = "DZ\characters\tops\torso3_m.p3d";
			female = "DZ\characters\tops\torso3_f.p3d";
		};
	};
	class AloneZFeet_Base: Clothing
	{
		scope = 1;
		displayName = "Bot Feet";
		model = "ai_bandits\models\proxy\Cube_G.p3d";
		inventorySlot[] = {"AloneZFeet"};
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"#(argb,8,8,3)color(0.843137,0.768627,0.658824,1.0,CO)"};
		hiddenSelectionsMaterials[] = {"DZ\characters\heads\data\hhl_dummy_skin_material.rvmat"};
		class ClothingTypes
		{
			male = "DZ\characters\shoes\feet3_m.p3d";
			female = "DZ\characters\shoes\feet3_m.p3d";
		};
	};
	class AloneZHands_Base: Clothing
	{
		scope = 1;
		displayName = "Bot Hands";
		model = "ai_bandits\models\proxy\Cube_G.p3d";
		inventorySlot[] = {"AloneZHands"};
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"#(argb,8,8,3)color(0.843137,0.768627,0.658824,1.0,CO)"};
		hiddenSelectionsMaterials[] = {"dz\characters\heads\data\hhl_dummy_skin_material.rvmat"};
		class ClothingTypes
		{
			male = "DZ\characters\gloves\hands3_m.p3d";
			female = "DZ\characters\gloves\hands3_f.p3d";
		};
	};
	class AloneZLegs_Base: Clothing
	{
		scope = 1;
		displayName = "Bot Legs";
		model = "ai_bandits\models\proxy\Cube_G.p3d";
		inventorySlot[] = {"AloneZLegs"};
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"#(argb,8,8,3)color(0.843137,0.768627,0.658824,1.0,CO)"};
		hiddenSelectionsMaterials[] = {"dz\characters\heads\data\hhl_dummy_skin_material.rvmat"};
		class ClothingTypes
		{
			male = "DZ\characters\pants\legs3_m.p3d";
			female = "DZ\characters\pants\legs3_f.p3d";
		};
	};

	class Head_Default;
	class AloneZHead_Base: Head_Default
	{
		scope = 0;
		displayName = "Bot Head";
		descriptionShort = "AI bot head";
		model = "\dz\characters\heads\m_adam.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {};
		hiddenSelectionsMaterials[] = {};
	};
	class AloneZHead_Adam: AloneZHead_Base
	{
		scope = 2;
		model = "dz\characters\heads\m_adam.p3d";
		hiddenSelectionsTextures[] = {"dz\characters\heads\data\m_adam\hhl_m_adam_body_bearded_co.paa"};
		hiddenSelectionsMaterials[] = {"dz\characters\heads\data\m_adam\hhl_m_adam_body_bearded.rvmat"};
	};
	class AloneZHead_Boris: AloneZHead_Base
	{
		scope = 2;
		model = "dz\characters\heads\m_boris.p3d";
		hiddenSelectionsTextures[] = {"dz\characters\heads\data\m_boris\hhl_m_boris_body_bearded_co.paa"};
		hiddenSelectionsMaterials[] = {"dz\characters\heads\data\m_boris\hhl_m_boris_body_bearded.rvmat"};
	};
	class AloneZHead_Cyril: AloneZHead_Base
	{
		scope = 2;
		model = "dz\characters\heads\m_cyril.p3d";
		hiddenSelectionsTextures[] = {"dz\characters\heads\data\m_cyril\hhl_m_cyril_beard_ca.paa", "", "dz\characters\heads\data\m_cyril\hhl_m_cyril_body_bearded_co.paa"};
		hiddenSelectionsMaterials[] = {"dz\characters\heads\data\m_cyril\hhl_m_cyril_beard.rvmat", "", "dz\characters\heads\data\m_cyril\hhl_m_cyril_body_bearded.rvmat"};
	};
	class AloneZHead_Denis: AloneZHead_Base
	{
		scope = 2;
		model = "dz\characters\heads\m_denis_2.p3d";
		hiddenSelectionsTextures[] = {"dz\characters\heads\data\m_Denis_2\hhl_m_Denis_beard_ca.paa", "", "dz\characters\heads\data\m_Denis_2\hhl_m_Denis_body_bearded_co.paa"};
		hiddenSelectionsMaterials[] = {"dz\characters\heads\data\m_Denis_2\hhl_m_Denis_beard.rvmat", "", "dz\characters\heads\data\m_Denis_2\hhl_m_Denis_body_bearded.rvmat"};
	};
	class AloneZHead_Elias: AloneZHead_Base
	{
		scope = 2;
		model = "dz\characters\heads\m_elias.p3d";
		hiddenSelectionsTextures[] = {"dz\characters\heads\data\m_Elias\hhl_m_Elias_beard_ca.paa", "", "dz\characters\heads\data\m_Elias\hhl_m_Elias_body_bearded_co.paa"};
		hiddenSelectionsMaterials[] = {"dz\characters\heads\data\m_Elias\hhl_m_Elias_beard.rvmat", "", "dz\characters\heads\data\m_Elias\hhl_m_Elias_body_bearded.rvmat"};
	};
	class AloneZHead_Francis: AloneZHead_Base
	{
		scope = 2;
		model = "dz\characters\heads\m_francis.p3d";
		hiddenSelectionsTextures[] = {"dz\characters\heads\data\m_Francis\hhl_m_Francis_beard_ca.paa", "", "dz\characters\heads\data\m_Francis\hhl_m_Francis_body_bearded_co.paa"};
		hiddenSelectionsMaterials[] = {"dz\characters\heads\data\m_Francis\hhl_m_Francis_beard.rvmat", "", "dz\characters\heads\data\m_Francis\hhl_m_Francis_body_bearded.rvmat"};
	};

	class AloneZ_Bot_Male_Adam: AloneZ_Bot_MaleBase
	{
		scope = 2;
		Head = "AloneZHead_Adam";
	};
	class AloneZ_Bot_Male_Boris: AloneZ_Bot_MaleBase
	{
		scope = 2;
		Head = "AloneZHead_Boris";
	};
	class AloneZ_Bot_Male_Cyril: AloneZ_Bot_MaleBase
	{
		scope = 2;
		Head = "AloneZHead_Cyril";
	};
	class AloneZ_Bot_Male_Denis: AloneZ_Bot_MaleBase
	{
		scope = 2;
		Head = "AloneZHead_Denis";
	};
	class AloneZ_Bot_Male_Elias: AloneZ_Bot_MaleBase
	{
		scope = 2;
		Head = "AloneZHead_Elias";
	};
	class AloneZ_Bot_Male_Francis: AloneZ_Bot_MaleBase
	{
		scope = 2;
		Head = "AloneZHead_Francis";
	};

	// ====================================================================
	// OVERRIDE: Fix original AI_Bandits head classes
	// BanditHead_Base was Inventory_Base -> now Head_Default
	// This fixes the "must be inherited from class 'HeadType'" error
	// that makes bots invisible
	// ====================================================================

	class BanditHead_Base: Head_Default
	{
		scope = 0;
		displayName = "Bandit Head";
		model = "\dz\characters\heads\m_rolf.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {};
		hiddenSelectionsMaterials[] = {};
		wounds = "CfgWounds";
		selectionHeadWound = "injury_head";
		selectionPersonality = "personality";
	};
	class BanditHead_Keiko: Head_Default
	{
		scope = 2;
		displayName = "Keiko Head";
		model = "\dz\characters\heads\f_keiko.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"\dz\characters\heads\data\f_keiko_co.paa"};
		hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\f_keiko.rvmat"};
	};
	class BanditHead_Linda: Head_Default
	{
		scope = 2;
		displayName = "Linda Head";
		model = "\dz\characters\heads\f_linda_2.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"\dz\characters\heads\data\f_linda_2_co.paa"};
		hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\f_linda_2.rvmat"};
	};
	class BanditHead_Rolf: Head_Default
	{
		scope = 2;
		displayName = "Rolf Head";
		model = "\dz\characters\heads\m_rolf.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_rolf_co.paa"};
		hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_rolf.rvmat"};
	};
	class BanditHead_Denis: Head_Default
	{
		scope = 2;
		displayName = "Denis Head";
		model = "\dz\characters\heads\m_denis_2.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_denis_2_co.paa"};
		hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_denis_2.rvmat"};
	};
	class BanditHead_Adam: Head_Default
	{
		scope = 2;
		displayName = "Adam Head";
		model = "\dz\characters\heads\m_adam.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_adam_co.paa"};
		hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_adam.rvmat"};
	};
	class BanditHead_Boris: Head_Default
	{
		scope = 2;
		displayName = "Boris Head";
		model = "\dz\characters\heads\m_boris.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_boris_co.paa"};
		hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_boris.rvmat"};
	};
	class BanditHead_Cyril: Head_Default
	{
		scope = 2;
		displayName = "Cyril Head";
		model = "\dz\characters\heads\m_cyril.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_cyril_co.paa"};
		hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_cyril.rvmat"};
	};
	class BanditHead_Elias: Head_Default
	{
		scope = 2;
		displayName = "Elias Head";
		model = "\dz\characters\heads\m_elias.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_elias_co.paa"};
		hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_elias.rvmat"};
	};
	class BanditHead_Francis: Head_Default
	{
		scope = 2;
		displayName = "Francis Head";
		model = "\dz\characters\heads\m_francis.p3d";
		hiddenSelections[] = {"personality"};
		hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_francis_co.paa"};
		hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_francis.rvmat"};
	};
};
