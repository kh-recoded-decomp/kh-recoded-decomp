#ifndef EVENT_2D_PANEL_H
#define EVENT_2D_PANEL_H

#include "nitro/types.h"

typedef int (*Event2DPanelStateFn)(void);

typedef struct Event2DPanelArgs {
    u8 reserved00;
    s8 value01;
    s16 value02;
    s16 value04;
} Event2DPanelArgs;

typedef struct Event2DPanelSlot { u8 data[0x9c]; } Event2DPanelSlot;
typedef struct Event2DPanelActor { u8 data[0x138]; } Event2DPanelActor;
typedef struct Event2DScreenLayer { u8 data[0x54]; } Event2DScreenLayer;

typedef struct Event2DPanelWork {
    u16 value00;
    u16 value02;
    u16 value04;
    u16 flags;
    s32 state;
    void *pxiHandle;
    u8 channels[2][0x648];
    u8 reserved0ca0[0x1048 - 0xca0];
    void *resourceD;
    void *characterArchive;
    void *backgroundArchive;
    void *objectArchive;
    u32 projection[14];
    Event2DPanelSlot *slots;
    Event2DPanelActor *actors;
    Event2DScreenLayer *layers;
    u8 reserved109c[0x10fc - 0x109c];
} Event2DPanelWork;

typedef struct Event2DPanelManager {
    void *buffer;
    Event2DPanelWork *work;
    void *extra;
} Event2DPanelManager;

typedef char Event2DPanelWorkSize[sizeof(Event2DPanelWork) == 0x10fc ? 1 : -1];
typedef char Event2DPanelChannelOffset[(u32)&((Event2DPanelWork *)0)->channels == 0x10 ? 1 : -1];
typedef char Event2DPanelProjectionOffset[(u32)&((Event2DPanelWork *)0)->projection == 0x1058 ? 1 : -1];
typedef char Event2DPanelSlotOffset[(u32)&((Event2DPanelWork *)0)->slots == 0x1090 ? 1 : -1];
typedef char Event2DPanelActorSize[sizeof(Event2DPanelActor) == 0x138 ? 1 : -1];
typedef char Event2DPanelSlotSize[sizeof(Event2DPanelSlot) == 0x9c ? 1 : -1];
typedef char Event2DScreenLayerSize[sizeof(Event2DScreenLayer) == 0x54 ? 1 : -1];

extern Event2DPanelManager data_ov036_020c3940;
Event2DPanelStateFn InitEvent2DPanel(Event2DPanelArgs *args);

#endif
