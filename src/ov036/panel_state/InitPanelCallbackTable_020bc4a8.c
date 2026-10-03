#include "nitro/types.h"

typedef void (*PanelCallback)(void);

typedef struct PanelCallbackTable {
    PanelCallback callbacks[9];
} PanelCallbackTable;

extern void func_ov036_020bc384(void);
extern void func_ov036_020bc3a8(void);
extern void func_ov036_020bc3d4(void);
extern void func_ov036_020bc3f8(void);
extern void IsPxiFifoTagSet_020bc414(void);
extern void InvalidatePxiFifoTag_020bc438(void);
extern void RecordPanelInputEvent_020bc458(void);
extern void func_ov036_020bc4a0(void);
extern void func_ov036_020bb284(void);

void InitPanelCallbackTable_020bc4a8(PanelCallbackTable *table)
{
    table->callbacks[0] = func_ov036_020bc384;
    table->callbacks[1] = func_ov036_020bc3a8;
    table->callbacks[2] = func_ov036_020bc3d4;
    table->callbacks[3] = func_ov036_020bc3f8;
    table->callbacks[4] = IsPxiFifoTagSet_020bc414;
    table->callbacks[5] = InvalidatePxiFifoTag_020bc438;
    table->callbacks[6] = RecordPanelInputEvent_020bc458;
    table->callbacks[7] = func_ov036_020bc4a0;
    table->callbacks[8] = func_ov036_020bb284;
}
