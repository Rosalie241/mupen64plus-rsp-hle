#include "Zilmar_Settings.h"
#include "Zilmar_Rsp.h"

enum SettingDataType
{
    Data_DWORD = 0,
    Data_String = 1,
    Data_CPUTYPE = 2,
    Data_SelfMod = 3,
    Data_OnOff = 4,
    Data_YesNo = 5,
    Data_SaveChip = 6
};

enum SettingLocation
{
    SettingType_ConstString = 0,
    SettingType_ConstValue = 1,
    SettingType_CfgFile = 2,
    SettingType_Registry = 3,
    SettingType_RelativePath = 4,
    TemporarySetting = 5,
    SettingType_RomDatabase = 6,
    SettingType_CheatSetting = 7,
    SettingType_GameSetting = 8,
    SettingType_BoolVariable = 9,
    SettingType_NumberVariable = 10,
    SettingType_StringVariable = 11,
    SettingType_SelectedDirectory = 12,
    SettingType_RdbSetting = 13,
};

typedef struct
{
    uint32_t dwSize;
    int DefaultStartRange;
    int SettingStartRange;
    int MaximumSettings;
    int NoDefault;
    int DefaultLocation;
    void * handle;

    unsigned int(*GetSetting)      (void * handle, int ID);
    const char * (*GetSettingSz)    (void * handle, int ID, char * Buffer, int BufferLen);
    void(*SetSetting)      (void * handle, int ID, unsigned int Value);
    void(*SetSettingSz)    (void * handle, int ID, const char * Value);
    void(*RegisterSetting) (void * handle, int ID, int DefaultID, enum SettingDataType Type,
        enum SettingLocation Location, const char * Category, const char * DefaultStr, uint32_t Value);
    void(*UseUnregisteredSetting) (int ID);
} PLUGIN_SETTINGS;

typedef struct
{
    unsigned int(*FindSystemSettingId) (void * handle, const char * Name);
} PLUGIN_SETTINGS2;

static PLUGIN_SETTINGS  g_PluginSettings;
static PLUGIN_SETTINGS2 g_PluginSettings2;

EXPORT void CALL SetSettingInfo(PLUGIN_SETTINGS * info)
{
    g_PluginSettings = *info;
}

EXPORT void CALL SetSettingInfo2(PLUGIN_SETTINGS2 * info)
{
    g_PluginSettings2 = *info;
}

int16_t CALL FindSystemSettingId(const char * Name)
{
	if (g_PluginSettings2.FindSystemSettingId && g_PluginSettings.handle)
    {
        return (int16_t)g_PluginSettings2.FindSystemSettingId(g_PluginSettings.handle, Name);
    }
    return 0;
}

uint32_t CALL GetSystemSetting(int16_t SettingID)
{
	return g_PluginSettings.GetSetting(g_PluginSettings.handle, SettingID);
}
