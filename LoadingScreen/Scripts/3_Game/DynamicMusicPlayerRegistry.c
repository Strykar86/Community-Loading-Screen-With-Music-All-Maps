modded class DynamicMusicPlayerRegistry
{
    protected override void RegisterTracksMenu()
    {
        m_TracksMenu = new array<ref DynamicMusicTrackData>();
        RegisterTrackMenu("YourModName_Music_Soundset");
    }
}