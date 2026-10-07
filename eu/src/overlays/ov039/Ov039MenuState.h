#ifndef KH_RECODED_OV039_MENU_STATE_H
#define KH_RECODED_OV039_MENU_STATE_H

#include "nitro/types.h"

typedef struct Ov039MenuState {
    u8 pad_0000[0x647c];
    u8 widgetContainer[0x647c];
    u8 primaryElement[0x4c];
    u8 secondaryElementPrefix[0x50];
    int selection;
    void *activeScene;
    void *sharedState;
    u8 secondaryElementSuffix[0x78];
    BOOL primaryElementEnabled;
    BOOL secondaryElementEnabled;
    u8 pad_ca20[0x44];
    u8 input[1];
    u8 pad_ca65[0x1b];
    u32 flags;
    u8 pad_ca84[0x24];
    u8 font[0x2c];
    u32 stackDepth;
    u32 stackEntries[1];
} Ov039MenuState;

extern Ov039MenuState *data_ov039_020bea20;
#define gOv039MenuState data_ov039_020bea20

#endif
