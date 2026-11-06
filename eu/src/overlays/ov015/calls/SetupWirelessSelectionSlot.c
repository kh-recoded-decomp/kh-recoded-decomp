#include "src/overlays/ov015/WirelessMenuContext.h"
#include "src/overlays/ov015/WirelessPanelInitData.h"

typedef struct SelectionWidget {
    u8 reserved00[0xc];
    s32 id;
    u32 reserved10;
    s32 recordIndex;
} SelectionWidget;

extern WirelessMenuContext *gWirelessMenuWork;
extern const PanelWidgetIds gWirelessSelectionPriorityWidgetIds;
extern void ResetSelectionView(WirelessSelectionView *view);
extern void SetGroupSlotsVisible(void *manager, WirelessSelectionView *view, BOOL visible);
extern SelectionWidget *FindWidgetById(void *manager, s32 id);
extern void SetIndexedRecordPriority(void *manager, s32 index, s32 priority);

static inline WirelessSelectionView *GetSelectionView(WirelessMenuContext *context,
                                                      s32 slot)
{
    return &context->views[slot];
}

void SetupWirelessSelectionSlot(s32 slot, WidgetPoint *position)
{
    PanelWidgetIds widgetIds = gWirelessSelectionPriorityWidgetIds;
    void *manager;
    SelectionWidget *widget;

    gWirelessMenuWork->views[slot].selection =
        &gWirelessMenuWork->selections[slot];
    ResetSelectionView(&gWirelessMenuWork->views[slot]);
    gWirelessMenuWork->views[slot].basePriority = 200;
    gWirelessMenuWork->views[slot].flags.mode = 1;
    gWirelessMenuWork->views[slot].flags.flag2 = 1;
    if (position != NULL) {
        GetSelectionView(gWirelessMenuWork, slot)->position = *position;
    }
    BuildSelectionViewRecords(gWirelessMenuWork->widgetManager,
                       &gWirelessMenuWork->views[slot]);
    SetGroupSlotsVisible(gWirelessMenuWork->widgetManager,
                         &gWirelessMenuWork->views[slot], TRUE);
    manager = gWirelessMenuWork->widgetManager;
    widget = FindWidgetById(manager, widgetIds.ids[slot]);
    SetIndexedRecordPriority(manager, widget->recordIndex, 252);
}
