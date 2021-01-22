#ifndef ZILMAR_SETTINGS_H
#define ZILMAR_SETTINGS_H

#include <stdint.h>

extern int16_t FindSystemSettingId(const char * Name);
extern uint32_t GetSystemSetting(int16_t SettingID);

#endif // ZILMAR_SETTINGS_H