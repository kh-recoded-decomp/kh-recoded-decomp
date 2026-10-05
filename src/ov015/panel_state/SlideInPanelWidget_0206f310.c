#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int ids[3];
} WidgetIdTable;

typedef struct {
    fx32 x;
    fx32 y;
} WidgetPos;

typedef struct {
    u8 pad_0000[0x34];
    WidgetPos pos;
} Widget;

typedef struct {
    u8 pad_0000[0x6ac0];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov015_0207e960;
extern const WidgetIdTable data_ov015_02079f70;
extern Widget *func_ov027_020b90a4(void *panel, int elementId);
extern void ApplySelectedSubitemValues_020b94fc(void *panel, Widget *widget, int useAlt);
extern void func_ov027_020b91c8(void *panel, Widget *widget, const WidgetPos *position, int mode);
extern void StartWidgetMoveTween_020b9428(void *root, Widget *widget, int duration, const WidgetPos *from, const WidgetPos *to, int mode);
extern void SetEntrySlotsVisible_020b9580(void *panel, Widget *widget, int visible);
extern void func_ov027_020b95e4(void *panel, Widget *widget);

void SlideInPanelWidget_0206f310(int index)
{
    WidgetIdTable table;
    WidgetPos from;
    WidgetPos to;
    Widget *widget;

    table = data_ov015_02079f70;
    widget = func_ov027_020b90a4(data_ov015_0207e960->panel, table.ids[index]);
    ApplySelectedSubitemValues_020b94fc(data_ov015_0207e960->panel, widget, 1);
    from = widget->pos;
    to = widget->pos;
    from.y = 0x12c000;
    func_ov027_020b91c8(data_ov015_0207e960->panel, widget, &from, 0);
    StartWidgetMoveTween_020b9428(data_ov015_0207e960->panel, widget, 2, &from, &to, 0x9c4);
    SetEntrySlotsVisible_020b9580(data_ov015_0207e960->panel, widget, 1);
    func_ov027_020b95e4(data_ov015_0207e960->panel, widget);
}
