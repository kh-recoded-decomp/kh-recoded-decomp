#include "src/overlays/ov027/WidgetRecordOps.h"
#include "nitro/types.h"
#include "nitro/hw.h"

typedef struct {
    u8 pad_00[0xe4];
    u32 unk_E4;
    u8 pad_E8[0x6ac0 - 0xe8];
    u8 container[4];
} PanelState;

extern void *FindWidgetById(void *container, int itemId);
extern int GetOv002PanelMessage(int textIndex, int unused);
extern void DrawPanelTextLine(int screen, int x, int y, int size, int arg4, int arg5, int textId, int arg7);
extern void InitMenuCursorState(int mode);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern PanelState *gWirelessMenuWork;

void InitWirelessPanelConfirmWidgets(void) {
    void *container;

    *(vu32 *)REG_DB_DISPCNT_ADDR = (*(vu32 *)REG_DB_DISPCNT_ADDR & ~0x1f00) | 0x1f00;
    DrawPanelTextLine(0, 0x80, 0x32, 2, 6, 10, GetOv002PanelMessage(0x70, 0), 0);
    gWirelessMenuWork->unk_E4 = 0;
    InitMenuCursorState(0);
    container = gWirelessMenuWork->container;
    ClearWidgetRecordActiveBits(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 0xb)));
    container = gWirelessMenuWork->container;
    ClearWidgetRecordActiveBits(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 0x1e)));
    container = gWirelessMenuWork->container;
    ClearWidgetRecordActiveBits(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 0x1f)));
    container = gWirelessMenuWork->container;
    ClearWidgetRecordActiveBits(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 0x20)));
    container = gWirelessMenuWork->container;
    ClearWidgetRecordActiveBits(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 0x21)));
    container = gWirelessMenuWork->container;
    ClearWidgetRecordActiveBits(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 9)));
    container = gWirelessMenuWork->container;
    ClearWidgetRecordActiveBits(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 0x11)));
    container = gWirelessMenuWork->container;
    SetWidgetAnimationFrame(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 0x11)), 0);
    PlaySoundEffect(2, 3);
}
