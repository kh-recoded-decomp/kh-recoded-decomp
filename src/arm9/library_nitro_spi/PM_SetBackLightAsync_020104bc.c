#include "nitro/types.h"

typedef void (*PMCallback)(u32 result, void *arg);

enum {
    PM_LCD_TOP = 0,
    PM_LCD_BOTTOM = 1,
    PM_LCD_ALL = 2
};

enum {
    PM_BACKLIGHT_OFF = 0,
    PM_BACKLIGHT_ON = 1
};

enum {
    PM_UTIL_LCD1_BACKLIGHT_ON = 4,
    PM_UTIL_LCD1_BACKLIGHT_OFF = 5,
    PM_UTIL_LCD2_BACKLIGHT_ON = 6,
    PM_UTIL_LCD2_BACKLIGHT_OFF = 7,
    PM_UTIL_LCD12_BACKLIGHT_ON = 8,
    PM_UTIL_LCD12_BACKLIGHT_OFF = 9
};

#define PM_INVALID_COMMAND 0xffff

extern u32 PMi_SendChannelValueAsync_02010418(u32 channel, u32 value, u32 reserved, PMCallback callback, void *arg);

u32 PM_SetBackLightAsync_020104bc(int target, int sw, PMCallback callback, void *arg)
{
    u32 command = 0;

    if (target == PM_LCD_TOP) {
        if (sw == PM_BACKLIGHT_ON) {
            command = PM_UTIL_LCD2_BACKLIGHT_ON;
        }
        if (sw == PM_BACKLIGHT_OFF) {
            command = PM_UTIL_LCD2_BACKLIGHT_OFF;
        }
    } else if (target == PM_LCD_BOTTOM) {
        if (sw == PM_BACKLIGHT_ON) {
            command = PM_UTIL_LCD1_BACKLIGHT_ON;
        }
        if (sw == PM_BACKLIGHT_OFF) {
            command = PM_UTIL_LCD1_BACKLIGHT_OFF;
        }
    } else if (target == PM_LCD_ALL) {
        if (sw == PM_BACKLIGHT_ON) {
            command = PM_UTIL_LCD12_BACKLIGHT_ON;
        }
        if (sw == PM_BACKLIGHT_OFF) {
            command = PM_UTIL_LCD12_BACKLIGHT_OFF;
        }
    }

    return command ? PMi_SendChannelValueAsync_02010418(command, 0, 0, callback, arg) : PM_INVALID_COMMAND;
}
