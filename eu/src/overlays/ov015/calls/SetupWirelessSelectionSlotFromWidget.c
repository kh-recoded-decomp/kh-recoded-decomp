#include "src/overlays/ov027/WidgetRecordOps.h"
#include "src/overlays/ov015/WirelessMenuContext.h"
#include "src/overlays/ov015/WirelessPanelInitData.h"

extern WirelessMenuContext *gWirelessMenuWork;
extern const PanelWidgetIds gWirelessSelectionSourceWidgetIds;
extern void *FindWidgetById(void *target, int id);
extern void SetEntrySlotsVisible(void *target, void *obj, int flag);
extern void ApplySelectedSubitemValues(void *target, void *obj, int useAlt);

void SetupWirelessSelectionSlotFromWidget(int slotIndex) {
    PanelWidgetIds ids;
    int id;
    void *obj;
    void *target;
    WidgetPoint position;

    ids = gWirelessSelectionSourceWidgetIds;
    id = ids.ids[slotIndex];

    target = gWirelessMenuWork->widgetManager;
    obj = FindWidgetById(target, id);
    ResolveWidgetPositionComponents(target, obj, &position, WIDGET_POSITION_COMBINED_XY);

    target = gWirelessMenuWork->widgetManager;
    obj = FindWidgetById(target, id);
    SetEntrySlotsVisible(target, obj, 1);

    target = gWirelessMenuWork->widgetManager;
    obj = FindWidgetById(target, id);
    ClearWidgetRecordActiveBits(target, (const struct WidgetPositionRecord *)(obj));

    target = gWirelessMenuWork->widgetManager;
    obj = FindWidgetById(target, id);
    ApplySelectedSubitemValues(target, obj, 1);

    SetupWirelessSelectionSlot(slotIndex, &position);
}
