#ifndef RECODED_CONFIG_OPTION_H
#define RECODED_CONFIG_OPTION_H

#include "nitro/types.h"

typedef struct ConfigChoice {
    const void *name;
    const void *description;
} ConfigChoice;

typedef struct ConfigOption {
    u8 count;
    u8 value;
    u16 bitWidth : 2;
    u16 locked : 1;
    u16 bitIndex : 13;
    const void *label;
    ConfigChoice choices[1];
} ConfigOption;

typedef char ConfigChoiceSize[sizeof(ConfigChoice) == 8 ? 1 : -1];
typedef char ConfigOptionSize[sizeof(ConfigOption) == 0x10 ? 1 : -1];

extern ConfigOption *ConfigMenu_CreateOption(void *messages, u16 labelIndex, s8 count, u16 spec);

#endif
