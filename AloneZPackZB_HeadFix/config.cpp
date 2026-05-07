// ============================================================================
// AloneZPackZB_HeadFix — Override AI_Bandits head classes
// ============================================================================
// The original AI_Bandits PBO defines BanditHead_Base : Inventory_Base,
// but DayZ requires all head attachment classes to inherit from Head_Default
// (entityType = HeadType). This causes:
//   ENTITY (E): Type 'Inventory_BaseType' must be inherited from class 'HeadType'
// ...and makes the bot invisible (head fails to attach, no body renders).
//
// This config re-declares the BanditHead classes with the correct parent
// (Head_Default) and adds all required head properties (wounds, selections, etc).
//
// IMPORTANT: requiredAddons includes "AI_Bandits" so the engine processes
// AI_Bandits config FIRST, then this config OVERRIDES the broken classes.
// The RPT should show: "Updating base class Inventory_Base->Head_Default"
// ============================================================================

class CfgPatches
{
    class AloneZPackZB_HeadFix
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Characters_Heads", "AI_Bandits"};
    };
};

class CfgVehicles
{
    // Forward-declare the DayZ base head class
    class Head_Default;

    // ========================================================================
    // Override BanditHead_Base: change parent from Inventory_Base to Head_Default
    // ========================================================================
    class BanditHead_Base: Head_Default
    {
        scope = 0;
        model = "\dz\characters\heads\m_rolf.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {};
        hiddenSelectionsMaterials[] = {};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };

    // ========================================================================
    // Override each BanditHead variant with correct inheritance + properties
    // ========================================================================

    // --- Keiko (female) ---
    class BanditHead_Keiko: BanditHead_Base
    {
        scope = 2;
        displayName = "Keiko Head";
        model = "\dz\characters\heads\f_keiko.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {"\dz\characters\heads\data\f_keiko_co.paa"};
        hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\f_keiko.rvmat"};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };

    // --- Linda (female) ---
    class BanditHead_Linda: BanditHead_Base
    {
        scope = 2;
        displayName = "Linda Head";
        model = "\dz\characters\heads\f_linda_2.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {"\dz\characters\heads\data\f_linda_2_co.paa"};
        hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\f_linda_2.rvmat"};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };

    // --- Rolf (male) ---
    class BanditHead_Rolf: BanditHead_Base
    {
        scope = 2;
        displayName = "Rolf Head";
        model = "\dz\characters\heads\m_rolf.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_rolf_co.paa"};
        hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_rolf.rvmat"};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };

    // --- Denis (male) ---
    class BanditHead_Denis: BanditHead_Base
    {
        scope = 2;
        displayName = "Denis Head";
        model = "\dz\characters\heads\m_denis_2.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_denis_2_co.paa"};
        hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_denis_2.rvmat"};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };

    // --- Adam (male) ---
    class BanditHead_Adam: BanditHead_Base
    {
        scope = 2;
        displayName = "Adam Head";
        model = "\dz\characters\heads\m_adam.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_adam_co.paa"};
        hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_adam.rvmat"};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };

    // --- Boris (male) ---
    class BanditHead_Boris: BanditHead_Base
    {
        scope = 2;
        displayName = "Boris Head";
        model = "\dz\characters\heads\m_boris.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_boris_co.paa"};
        hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_boris.rvmat"};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };

    // --- Cyril (male) ---
    class BanditHead_Cyril: BanditHead_Base
    {
        scope = 2;
        displayName = "Cyril Head";
        model = "\dz\characters\heads\m_cyril.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_cyril_co.paa"};
        hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_cyril.rvmat"};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };

    // --- Elias (male) ---
    class BanditHead_Elias: BanditHead_Base
    {
        scope = 2;
        displayName = "Elias Head";
        model = "\dz\characters\heads\m_elias.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_elias_co.paa"};
        hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_elias.rvmat"};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };

    // --- Francis (male) ---
    class BanditHead_Francis: BanditHead_Base
    {
        scope = 2;
        displayName = "Francis Head";
        model = "\dz\characters\heads\m_francis.p3d";
        hiddenSelections[] = {"personality"};
        hiddenSelectionsTextures[] = {"\dz\characters\heads\data\m_francis_co.paa"};
        hiddenSelectionsMaterials[] = {"\dz\characters\heads\data\m_francis.rvmat"};
        wounds = "CfgWounds";
        selectionHeadWound = "injury_head";
        selectionPersonality = "personality";
    };
};
