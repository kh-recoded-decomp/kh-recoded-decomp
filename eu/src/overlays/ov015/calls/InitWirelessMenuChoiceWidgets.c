#include "src/overlays/ov027/WidgetRecordOps.h"
#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 value;
} PanelItem;

typedef struct {
    u8 pad_00[0xbb];
    u8 unk_BB;
    u8 pad_BC[0xc];
    u32 selectedValue;
    u8 pad_CC[0x6ac0 - 0xcc];
    u8 container[4];
} PanelState;

extern PanelItem *FindWidgetById(void *container, int itemId);
extern void SetEntrySlotsVisible(void *container, PanelItem *item, int flag);
extern void ApplySelectedSubitemValues(void *container, PanelItem *item, int useAlt);
extern void SetFocusedWidget(void *container, PanelItem *item);
extern void SetWidgetRootInputCallback(void *container, u32 callback);
extern void DrawWirelessPanelChoiceLabels(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void UpdatePanelSelectionSound(PanelItem *item);
extern PanelState *gWirelessMenuWork;

void InitWirelessMenuChoiceWidgets(void) {
    void *container;

    container = gWirelessMenuWork->container;
    SetEntrySlotsVisible(container, FindWidgetById(container, 4), 1);
    container = gWirelessMenuWork->container;
    SetEntrySlotsVisible(container, FindWidgetById(container, 7), 1);
    container = gWirelessMenuWork->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 7), 1);
    container = gWirelessMenuWork->container;
    SetEntrySlotsVisible(container, FindWidgetById(container, 8), 1);
    container = gWirelessMenuWork->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 8), 1);
    container = gWirelessMenuWork->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 1), 0);
    container = gWirelessMenuWork->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 2), 0);
    container = gWirelessMenuWork->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 3), 0);
    SetFocusedWidget(gWirelessMenuWork->container, FindWidgetById(gWirelessMenuWork->container, 8));
    gWirelessMenuWork->selectedValue = FindWidgetById(gWirelessMenuWork->container, 8)->value;
    DrawWirelessPanelChoiceLabels();
    gWirelessMenuWork->unk_BB = 0;
    SetWidgetRootInputCallback(gWirelessMenuWork->container, (u32)UpdatePanelSelectionSound);
    PlaySoundEffect(2, 2);
    container = gWirelessMenuWork->container;
    ClearWidgetRecordActiveBits(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 9)));
    container = gWirelessMenuWork->container;
    SetWidgetAnimationFrame(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 9)), 0);
}
