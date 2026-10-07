#ifndef KH_RECODED_OV039_MENU_STATE_H
#define KH_RECODED_OV039_MENU_STATE_H

#include "nitro/fx_types.h"
#include "nitro/types.h"

typedef struct Ov039MenuState {
    u8 pad_0000[0x647c];
    u8 widgetContainer[0x647c];
    u8 primaryElement[0x4c];
    u8 secondaryElement[0x4c];
    void *heapHandle;
    int selection;
    void *activeScene;
    void *sharedState;
    u8 tileTable[0x28];
    fx32 brightness;
    fx32 subBrightness;
    u8 brightnessTween[0x1c];
    u8 subBrightnessTween[0x24];
    BOOL secondaryEnabled;
    BOOL inputEnabled;
    BOOL primaryElementEnabled;
    BOOL secondaryElementEnabled;
    u8 pad_ca20[2];
    u8 layerMask;
    u8 pad_ca23;
    BOOL vblankPending;
    BOOL busy;
    u8 pad_ca2c[0x18];
    u8 startDelay;
    u8 pad_ca45[5];
    u16 inputSource[1];
    u8 pad_ca4c[0x18];
    u8 input[0x10];
    u8 taskList[0xc];
    u32 flags;
    u8 font08[0xc];
    u8 font10[0xc];
    u8 font08s[0xc];
    u8 font10s[0xc];
    u8 pad_cab4[0x10];
    u8 packedView[0xc];
    BOOL firstVisit;
    u32 stackDepth;
    u32 stackEntries[5];
    int objectId;
} Ov039MenuState;

extern Ov039MenuState *data_ov039_020bea20;
#define gOv039MenuState data_ov039_020bea20

#endif
