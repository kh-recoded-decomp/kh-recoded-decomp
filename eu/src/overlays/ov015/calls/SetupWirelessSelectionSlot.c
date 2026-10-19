#include "src/overlays/ov015/WirelessMenuContext.h"
#include "src/overlays/ov015/WirelessPanelInitData.h"

typedef struct SelectionWidget {
    u8 reserved00[0xc];
    s32 id;
    u32 reserved10;
    s32 recordIndex;
} SelectionWidget;

extern WirelessMenuContext *data_ov015_0207e960;
extern const PanelWidgetIds data_ov015_02079f64;
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
    PanelWidgetIds widgetIds = data_ov015_02079f64;
    void *manager;
    SelectionWidget *widget;

    data_ov015_0207e960->views[slot].selection =
        &data_ov015_0207e960->selections[slot];
    ResetSelectionView(&data_ov015_0207e960->views[slot]);
    data_ov015_0207e960->views[slot].basePriority = 200;
    data_ov015_0207e960->views[slot].flags.mode = 1;
    data_ov015_0207e960->views[slot].flags.flag2 = 1;
    if (position != NULL) {
        GetSelectionView(data_ov015_0207e960, slot)->position = *position;
    }
    BuildSelectionViewRecords(data_ov015_0207e960->widgetManager,
                       &data_ov015_0207e960->views[slot]);
    SetGroupSlotsVisible(data_ov015_0207e960->widgetManager,
                         &data_ov015_0207e960->views[slot], TRUE);
    manager = data_ov015_0207e960->widgetManager;
    widget = FindWidgetById(manager, widgetIds.ids[slot]);
    SetIndexedRecordPriority(manager, widget->recordIndex, 252);
}
