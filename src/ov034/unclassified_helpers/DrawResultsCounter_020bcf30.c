#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenPoint {
    fx32 x;
    fx32 y;
} ScreenPoint;

extern void func_0204f0c0(void *objects, int slotIndex);
extern void *func_ov027_020b90a4(void *objects, int id);
extern ScreenPoint *func_ov027_020b91a8(void *objects, void *widget);
extern void func_ov027_020b95e4(void *objects, void *widget);
extern void func_ov027_020b96a0(void *objects, void *widget, int frame);
extern void func_ov027_020b9580(void *objects, void *widget, int visible);
extern int CreateObjectSlot_020bdea4(void *manager, int animation, int resource, int x, int y, int mode,
                                     int priority, int palette, int enabled);

void DrawResultsCounter_020bcf30(void *objects, int id, int resource, int value, int spacing, int *slots)
{
    int count;
    int i;
    void *widget;
    ScreenPoint pos;
    int offset;

    count = 0;
    offset = spacing;
    for (i = 0; i < 10; i++) {
        if (slots[i] >= 0) {
            func_0204f0c0(objects, slots[i]);
        }
        slots[i] = -1;
    }
    widget = func_ov027_020b90a4(objects, id);
    pos = *func_ov027_020b91a8(objects, widget);
    func_ov027_020b95e4(objects, widget);
    func_ov027_020b96a0(objects, widget, (u16)(value % 10));
    func_ov027_020b9580(objects, widget, 1);
    for (i = 0; i < 10; i++) {
        if (value < 10) {
            return;
        }
        slots[count++] = CreateObjectSlot_020bdea4(objects, 0, resource, (pos.x >> 12) - offset, pos.y >> 12, 1, 1,
                                                   value % 100 / 10, 1);
        value /= 10;
        offset += spacing;
    }
}
