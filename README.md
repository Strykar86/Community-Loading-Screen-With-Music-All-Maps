
# Universal DayZ Loading Screen & Music Pack
============================================
This is a powerful, all-in-one mod template designed to give server owners complete control over their loading and main menu experience. It combines a highly customizable visual loading screen with a dynamic music player that works for both the main menu and in-game loading sequences.

This project is built upon the robust scripts of the DayZ Expansion loading screen and has been generalized into a universal template that works on standard maps (Chernarus, Livonia) and includes overrides for special maps with their own loading screens (like Deer Isle).

## Features

* *   **Custom Rotating Backgrounds:** Display a list of your own custom images that rotate on a timer during all loading and queue screens.
*     
* *   **Custom Hints & Text:** Configure a list of custom hints, server rules, or welcome messages that appear during loading.
*     
* *   **Custom Menu & Loading Music:** Add your own pool of `.ogg` music tracks that will play in the main menu and continue through the loading screen.
*     
* *   **Customizable Loading Bar Color:** Easily change the color of the loading progress bar to match your server's theme.
*     
* *   **Custom Logo:** Replace the default DayZ logo with your own server's logo.
*     
* *   **Universal Map Support:** Works automatically on standard maps and includes the necessary override to replace the loading screen on maps like Deer Isle.
*     

## How to Use This Template

This repository is a template. To use it for your own server, follow these steps:

### Step 1: Setup & Renaming

First, you need to give your mod a unique name. Decide on a prefix for your project (e.g., `MyAwesomeServer`).

Using a text editor with a "Find and Replace in Files" feature (like VSCode), replace all instances of **`YourModName_LoadingPack`** with your new name (e.g., `MyAwesomeServer_LoadingPack`). You should also replace the generic **`YourModName`** in the `config.cpp` `CfgSoundSets` section with your prefix.

### Step 2: Adding Custom Images

1. 1.  Convert your desired loading screen images to `.paa` or `.edds` format using DayZ Tools.
1.     
1. 2.  Place your image files inside the `/Images/` folder.
1.     
1. 3.  Open `/Scripts/Data/LoadingImages.json` and update the `ImagePath` for each entry to point to your new files. The path must start from the root of your mod folder.
1.     

**Example `LoadingImages.json`:**

```
[
    {
        "ImagePath": "MyAwesomeServer_LoadingPack/Images/image1.paa"
    },
    {
        "ImagePath": "MyAwesomeServer_LoadingPack/Images/image2.paa"
    }
]
```

### Step 3: Adding Custom Hints

Open `/Scripts/Data/Hints.json` and edit the entries. `m_Headline` is the title of the hint, and `m_Description` is the main body of text.

**Example `Hints.json`:**

```
[
	{
		"m_Headline": "Welcome to Our Server!",
		"m_ImagePath": "",
		"m_Description": "Please be respectful to all players and join our Discord for server rules and events."
	},
	{
		"m_Headline": "Tip: Blood Types",
		"m_ImagePath": "",
		"m_Description": "Always check your blood type before accepting a transfusion. O- is the universal donor."
	}
]
```

### Step 4: Adding Custom Music

1. 1.  Convert your music tracks to the **`.ogg`** format.
1.     
1. 2.  Place your `.ogg` files inside the `/music/` folder.
1.     
1. 3.  Open the main `config.cpp` file and navigate to the `CfgSoundShaders` section.
1.     
1. 4.  Update the `samples[]` array with the correct paths to your music files. The path must start with a backslash `\` followed by your mod's folder name.
1.     

**Example `config.cpp` music section:**

```
class CfgSoundShaders 
{
	class MyAwesomeServer_Music_SoundShader 
	{
		samples[] = {
			{"\MyAwesomeServer_LoadingPack\music\theme1.ogg", 1},
			{"\MyAwesomeServer_LoadingPack\music\theme2.ogg", 1},
			{"\MyAwesomeServer_LoadingPack\music\epic_track.ogg", 1}
		};
		volume = 0.7;
	};
};
```

### Step 5: Customizing Colors & Logo

You can easily customize the loading bar color and logo by editing one script.

1. 1.  Open `/Scripts/3_Game/LoadingScreen.c`.
1.     
1. 2.  Near the top of the file, find the `class LoadingPack_Data`.
1.     
1. 3.  Edit the default values to your liking.
1.     

**Example `LoadingScreen.c` customization:**

```
class LoadingPack_Data
{
	bool ShowLogo = true;
	// Path to your custom logo file
	string LogoPath = "MyAwesomeServer_LoadingPack/GUI/logo.edds";
	bool RandomizeBackgounds = true;
	// ARGB format (Alpha, Red, Green, Blue) for the loading bar color
	int LoadingBarColor = ARGB(255, 0, 150, 255); // A nice blue color
	bool UseCustomHints = true;
	string HintIconPath = "MyAwesomeServer_LoadingPack/GUI/icons/circle_info.edds";

    // ... rest of the class
};
```

### Step 6: Packing & Deployment

Once you have finished customizing, use the DayZ Tools Addon Builder to pack your mod folder into a PBO. Then, upload it to your server and add it to your server's mod launch list.

## Troubleshoot

### How do I make a edds file ?

Near the end of this page you should have a quick tutorial: [https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/\[Modding\]-Adding-custom-loading-screen](https://github.com/salutesh/DayZ-Expansion-Scripts/wiki/%5BModding%5D-Adding-custom-loading-screen)

### The loading screen is white or shows a missing texture!

This almost always means the `ImagePath` in your `LoadingImages.json` is incorrect. Double-check that the path exactly matches your folder and file names. The path is case-sensitive!

### My custom music isn't playing!

* *   **Check `config.cpp`:** Ensure the filenames in the `CfgSoundShaders` section perfectly match your `.ogg` files in the `/music/` folder.
*     
* *   **Check the Path:** The path in `config.cpp` must start with a `\` (e.g., `\MyAwesomeServer_LoadingPack\music\track1.ogg`).
*     
* *   **File Format:** Make sure your music files are properly encoded as `.ogg`.
*     

### My mod doesn't seem to load at all.

If you are overriding a map like Deer Isle, make sure this mod is loaded **after** the Deer Isle mod in your server's launch parameters. For all other issues, it is likely a problem with how the PBO was packed. Ensure that your PBO packer is correctly including all file types (`.c`, `.json`, `.ogg`, etc.).

## Credits

This project is a fork and enhancement of the DayZ Expansion loading screen. Full credit to the original **DayZ Expansion Mod Team** and **Salutesh** for their excellent work which served as the foundation for this template.

