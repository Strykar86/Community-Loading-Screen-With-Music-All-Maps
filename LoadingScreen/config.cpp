class CfgPatches
{
	class YourModName_LoadingPack
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

// --- CORE MOD & SCRIPT DEFINITION ---
class CfgMods
{
	class YourModName_LoadingPack
	{
		dir = "YourModName_LoadingPack";
		name = "Your Custom Loading & Music Pack";
		credits = "YourName (Adapted from DayZ Expansion)";
		author = "YourName";
		type = "mod";
		dependencies[]= {"Game","World","Mission"};

		// This loads the modded class scripts for Chernarus, Livonia, etc.
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"YourModName_LoadingPack/Scripts/3_Game"};
			};
		};
	};
};

// --- MUSIC CONFIGURATION ---
class CfgSoundSets 
{
	class YourModName_Music_Soundset 
	{
		soundShaders[] = {"YourModName_Music_SoundShader"};
		volumeFactor = 1;
		frequencyFactor = 1;
		spatial = 0;
	};
};

class CfgSoundShaders 
{
	class YourModName_Music_SoundShader 
	{
		samples[] = {
			{"\YourModName_LoadingPack\music\track1", 1},
			{"\YourModName_LoadingPack\music\track2", 1}
		};
		volume = 0.7;
	};
};

// --- DEER ISLE & CUSTOM MAP OVERRIDE ---
class CfgMissions
{
	class CustomScenes
	{
		// This defines our loading screen as a "scene" that can be called by CfgWorlds
		class YourModName_LoadingScene
		{
			layout = "YourModName_LoadingPack/GUI/layouts/loading.layout";
			script = "YourModName_LoadingPack/Scripts/3_Game/LoadingScreen.c";
		};
	};
};

class CfgWorlds
{
	class deerisle  // This targets the Deer Isle map specifically
	{
        // This tells Deer Isle to use our new scene instead of its own
		cutscenes[] = {"YourModName_LoadingScene"};
	};
};