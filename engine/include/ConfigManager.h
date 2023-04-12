#pragma once
#include "GfxConfiguration.h"

class ConfigManager
{
public:
    void Initialize(GfxConfiguration* config);
    std::string GetRootFolder();
    std::string GetAssetFolder();
    std::string GetTextureFolder();
    std::string GetSoundFolder();
    std::string GetFontFolder();
    std::string GetFileFullPath(const std::string& name) const;
    std::string GetTextureFullPath(const std::string& name) const;
    std::string GetAssetFolderAbsolutePath();


private:
    std::string m_binary_root_folder;
    std::string m_binary_root_folder_absolutePath;
    std::string m_asset_folder;
    std::string m_texture_folder;
    std::string m_sound_folder;
    std::string m_font_folder;
};
