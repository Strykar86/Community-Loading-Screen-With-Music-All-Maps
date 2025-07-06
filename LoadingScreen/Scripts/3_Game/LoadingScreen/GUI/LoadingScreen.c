// --- DATA CLASSES ---
class LoadingPack_Background
{
	string ImagePath;
};

class LoadingPack_Data
{
	bool ShowLogo = true;
	string LogoPath = "YourModName_LoadingPack/GUI/logo.edds";
	bool RandomizeBackgounds = true;
	int LoadingBarColor = ARGB(255, 255, 255, 255); // Changed to white as a neutral default
	bool UseCustomHints = true;
	string HintIconPath = "YourModName_LoadingPack/GUI/icons/circle_info.edds";

	ref array<ref LoadingPack_Background> m_Backgrounds;

	void LoadingPack_Data()
	{
		m_Backgrounds = new array<ref LoadingPack_Background>;
		JsonFileLoader<array<ref LoadingPack_Background>>.JsonLoadFile("YourModName_LoadingPack/Scripts/Data/LoadingImages.json", m_Backgrounds);
	}
};

// --- MODDED GAME CLASSES ---
modded class UiHintPanel
{
	protected const string 	m_LoadingPack_HintsPath = "YourModName_LoadingPack/Scripts/Data/Hints.json";
	protected ref LoadingPack_Data m_LoadingPackData;

	override protected void LoadContentList()
	{
		if (!m_LoadingPackData)
			m_LoadingPackData = new LoadingPack_Data();

		if (m_LoadingPackData && m_LoadingPackData.UseCustomHints)
		{
			JsonFileLoader<array<ref HintPage>>.JsonLoadFile(m_LoadingPack_HintsPath, m_ContentList);
		}
		else
		{
			// Fallback to vanilla hints if disabled
			super.LoadContentList();
		}
	}
};

modded class LoginScreenBase
{
	protected int m_LoadingPack_BackgroundIndex = 0;
	protected const float LOADING_SCREEN_CHANGE_TIME = 3.0; // How often to change images
	protected float m_LoadingPack_TimeAccu;
	protected ImageWidget m_LoadingPack_Background;

	protected ref LoadingPack_Data m_LoadingPackData_Login;

	void LoginScreenBase()
	{
		m_LoadingPackData_Login = new LoadingPack_Data();
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		m_LoadingPack_TimeAccu += timeslice;
		if (m_LoadingPack_TimeAccu >= LOADING_SCREEN_CHANGE_TIME && m_LoadingPackData_Login && m_LoadingPackData_Login.m_Backgrounds.Count() > 0)
		{
			m_LoadingPack_BackgroundIndex++;
			if (m_LoadingPack_BackgroundIndex >= m_LoadingPackData_Login.m_Backgrounds.Count())
				m_LoadingPack_BackgroundIndex = 0;
			
			LoadingPack_SetBackgroundImage(m_LoadingPack_BackgroundIndex);
			m_LoadingPack_TimeAccu = 0;
		}
	}
	
	void LoadingPack_SetBackgroundImage(int index)
	{
		if (!m_LoadingPack_Background)
			m_LoadingPack_Background = ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));

		if (m_LoadingPackData_Login && m_LoadingPack_Background)
		{
			LoadingPack_Background background = m_LoadingPackData_Login.m_Backgrounds.Get(index);
			if (background && background.ImagePath != string.Empty)
			{
				m_LoadingPack_Background.LoadImageFile(0, background.ImagePath);
			}
		}
	}
};

modded class LoadingScreen
{
	protected ref LoadingPack_Data m_LoadingPackData_Loading;

	void LoadingScreen(DayZGame game)
	{
		m_LoadingPackData_Loading = new LoadingPack_Data();
		if (!m_LoadingPackData_Loading) return;

		// Remove vanilla mask texture to prevent image blending issues
		m_ImageWidgetBackground.LoadMaskTexture("");

		// Set custom loading bar color
		if (m_LoadingPackData_Loading.LoadingBarColor != 0)
		{
			m_ProgressLoading.SetColor(m_LoadingPackData_Loading.LoadingBarColor);
			ProgressAsync.SetProgressData(m_ProgressLoading);
		}

		// Set custom logo
		if (m_LoadingPackData_Loading.ShowLogo && m_LoadingPackData_Loading.LogoPath != string.Empty)
		{
			m_ImageLogoCorner.LoadImageFile(0, m_LoadingPackData_Loading.LogoPath);
			m_ImageLogoCorner.Show(true);
			m_ImageLogoMid.Show(false);
		}
		else
		{
			m_ImageLogoCorner.Show(false);
			m_ImageLogoMid.Show(false);
		}
	}

	override void Show()
	{
		// Set initial background image
		if (m_LoadingPackData_Loading && m_LoadingPackData_Loading.m_Backgrounds.Count() > 0)
		{
			string image_path = m_LoadingPackData_Loading.m_Backgrounds.GetRandomElement().ImagePath;
			m_ImageWidgetBackground.LoadImageFile(0, image_path);
		}
		
		super.Show();
	}
};