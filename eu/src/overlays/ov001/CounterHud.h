#ifndef EU_COUNTER_HUD_H
#define EU_COUNTER_HUD_H

#include "src/overlays/ov001/FieldMiscTables.h"

typedef struct HudDigit {
    s16 width;
    s16 height;
    u32 texture;
    u32 palette;
} HudDigit;

typedef struct HudModel {
    u8 data[0x104];
} HudModel;

typedef struct HudCounterField {
    u8 enabled : 1;
    u8 reserved : 7;
    u8 bitCount;
    u16 bitOffset;
} HudCounterField;

typedef struct CounterHud {
    s32 state;
    s32 fadeState;
    u8 reserved008[0x34 - 8];
    HudDigit digits[10];
    u8 reserved0ac[0xf0 - 0xac];
    BOOL enabled;
    u8 reserved0f4[4];
    BOOL fadeEnabled;
    u8 reserved0fc[4];
    fx32 animatedValue;
    u8 drawFlags;
    u8 reserved105[0x4dc - 0x105];
    HudModel panel;
    u8 reserved5e0[0x704 - 0x5e0];
    HudModel variants[2];
    HudCounterField counter;
} CounterHud;

typedef void (*HudHandler)(CounterHud *hud);

typedef struct CounterHandlers {
    HudHandler entries[6];
} CounterHandlers;

typedef struct FadeHandlers {
    HudHandler entries[5];
} FadeHandlers;

extern CounterHandlers gCounterHudStateHandlers;
extern FadeHandlers gFadeSequenceHandlers;

typedef char HudDigitSizeCheck[sizeof(HudDigit) == 12 ? 1 : -1];
typedef char HudModelSizeCheck[sizeof(HudModel) == 0x104 ? 1 : -1];
typedef char CounterHudSizeCheck[sizeof(CounterHud) == 0x910 ? 1 : -1];
typedef char CounterHudDrawFlagsOffsetCheck[
    (u32)&((CounterHud *)0)->drawFlags == 0x104 ? 1 : -1];
typedef char CounterHudPanelOffsetCheck[
    (u32)&((CounterHud *)0)->panel == 0x4dc ? 1 : -1];
typedef char CounterHudVariantsOffsetCheck[
    (u32)&((CounterHud *)0)->variants == 0x704 ? 1 : -1];
typedef char CounterHudCounterOffsetCheck[
    (u32)&((CounterHud *)0)->counter == 0x90c ? 1 : -1];

#endif
