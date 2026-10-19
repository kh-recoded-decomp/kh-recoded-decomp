#include "src/overlays/ov015/WirelessMenuContext.h"
#include "src/overlays/ov015/WirelessPanelInitData.h"

extern WirelessMenuContext *data_ov015_0207e960;
extern const PanelWidgetIds data_ov015_02079f58;
extern void *FindWidgetById(void *target, int id);
extern void SetEntrySlotsVisible(void *target, void *obj, int flag);
extern void func_ov027_020b9604(void *target, void *obj);
extern void ApplySelectedSubitemValues(void *target, void *obj, int useAlt);

void func_ov015_0206e658(int slotIndex) {
    PanelWidgetIds ids;
    int id;
    void *obj;
    void *target;
    WidgetPoint position;

    ids = data_ov015_02079f58;
    id = ids.ids[slotIndex];

    target = data_ov015_0207e960->widgetManager;
    obj = FindWidgetById(target, id);
    ResolveWidgetPositionComponents(target, obj, &position, WIDGET_POSITION_COMBINED_XY);

    target = data_ov015_0207e960->widgetManager;
    obj = FindWidgetById(target, id);
    SetEntrySlotsVisible(target, obj, 1);

    target = data_ov015_0207e960->widgetManager;
    obj = FindWidgetById(target, id);
    func_ov027_020b9604(target, obj);

    target = data_ov015_0207e960->widgetManager;
    obj = FindWidgetById(target, id);
    ApplySelectedSubitemValues(target, obj, 1);

    SetupWirelessSelectionSlot(slotIndex, &position);
}
