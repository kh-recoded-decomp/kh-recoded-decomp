#ifndef KH_RECODED_OV013_PANEL_STATE_H
#define KH_RECODED_OV013_PANEL_STATE_H

#include "nitro/types.h"
#include "src/overlays/ov027/WidgetPosition.h"

typedef struct PanelScrollList {
    s8 itemCount;
    s8 visibleCount;
    s8 rowInView;
    s8 scrollOffset;
    s8 cursor;
    u8 flags;
    u8 reserved06[2];
    s32 scrollPixels;
    s32 maxScrollPixels;
    s32 rowPixels;
    s32 rowHeight;
} PanelScrollList;

typedef char PanelScrollListMustBe24Bytes[
    sizeof(PanelScrollList) == 24 ? 1 : -1];

typedef struct PanelWidget {
    u8 reserved00[0xc];
    s32 id;
} PanelWidget;

typedef union PanelColor {
    u16 raw;
    struct {
        u16 red : 5;
        u16 green : 5;
        u16 blue : 5;
        u16 reserved : 1;
    };
} PanelColor;

typedef char PanelColorMustBe2Bytes[sizeof(PanelColor) == 2 ? 1 : -1];

typedef struct Ov013PanelState {
    s8 mode;
    u8 reserved01[2];
    u8 resultMode;
    s8 rowHeight;
    u8 reserved05[5];
    PanelColor baseColor;
    PanelColor pulseColor;
    u8 reserved0e[2];
    s32 selectedWidget;
    u8 reserved14[0x98 - 0x14];
    u8 moveCursorWithScroll : 1;
    u8 paletteAndScrollFlags : 6;
    u8 pulseIncreasing : 1;
    u8 reserved99;
    u8 flags;
    u8 reserved9b;
    WidgetPoint framePositions[9];
    WidgetPoint iconPositions[9];
    WidgetPoint digitPositions[9];
    WidgetPoint labelPositions[9];
    WidgetPoint valuePositions[9];
    u8 reserved204[0x2bc - 0x204];
    s32 step;
    u8 reserved2c0[0xc];
    s32 scrollOffset;
    u8 reserved2d0[4];
    s32 animationOffset;
    u8 reserved2d8[0x2ec - 0x2d8];
    PanelScrollList list;
    u8 reserved304[0x6818 - 0x304];
    u8 widgets[0x6470];
    u8 reservedcc88[0xd150 - 0xcc88];
    WidgetPositionRecord *frames[9];
    WidgetPositionRecord *icons[9];
    WidgetPositionRecord *digits[27];
    u8 reservedd204[0xd259 - 0xd204];
    u8 scrollStopped : 1;
    u8 scrollDown : 1;
    u8 scrollFlags : 6;
} Ov013PanelState;

typedef char Ov013PanelStepMustStartAt700Bytes[
    (u32)&((Ov013PanelState *)0)->step == 0x2bc ? 1 : -1];
typedef char Ov013PanelBaseColorMustStartAt10Bytes[
    (u32)&((Ov013PanelState *)0)->baseColor == 0xa ? 1 : -1];
typedef char Ov013PanelPulseColorMustStartAt12Bytes[
    (u32)&((Ov013PanelState *)0)->pulseColor == 0xc ? 1 : -1];
typedef char Ov013PanelWidgetsMustStartAt26648Bytes[
    (u32)&((Ov013PanelState *)0)->widgets == 0x6818 ? 1 : -1];
typedef char Ov013PanelListMustStartAt748Bytes[
    (u32)&((Ov013PanelState *)0)->list == 0x2ec ? 1 : -1];
typedef char Ov013PanelFramePositionsMustStartAt156Bytes[
    (u32)&((Ov013PanelState *)0)->framePositions == 0x9c ? 1 : -1];
typedef char Ov013PanelFramesMustStartAt53584Bytes[
    (u32)&((Ov013PanelState *)0)->frames == 0xd150 ? 1 : -1];
typedef char Ov013PanelStateMustBe53852Bytes[
    sizeof(Ov013PanelState) == 0xd25c ? 1 : -1];

typedef struct PanelStateCallbacks {
    void (*enter)(void);
    void (*update)(void);
    void (*exit)(void);
} PanelStateCallbacks;

typedef char PanelStateCallbacksMustBe12Bytes[
    sizeof(PanelStateCallbacks) == 12 ? 1 : -1];

extern PanelStateCallbacks gPanelStateCallbacks[12];
void ChangePanelMenuState(char nextState);
void ScrollPanelSlotWidgets(void);
void PulsePanelPaletteColor(void);

extern Ov013PanelState *data_ov013_02074ce0;
#define gOv013PanelState data_ov013_02074ce0

#endif
