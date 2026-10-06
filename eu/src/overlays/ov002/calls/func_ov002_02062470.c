#include "nitro/types.h"

typedef struct PanelFlags {
    u8 unused0 : 2;
    u8 initialized : 1;
    u8 unused3 : 5;
} PanelFlags;

typedef struct PanelState {
    u8 pad_00[0x10];
    PanelFlags flags10;
    u8 pad_11[0x48 - 0x11];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void DestroyFndObjectList(void *entry);
extern void InitTextLayerDefault(void *entry, int mode, int value, const u16 *data);

void func_ov002_02062470(int value) {
    u16 data[8];

    if (data_ov002_0206c460->flags10.initialized) {
        DestroyFndObjectList((u8 *)data_ov002_0206c460 + 0x48);
    }

    data[0] = 1;
    data[1] = 0;
    data[2] = 0x1f;
    data[3] = 0xf;
    data[4] = 1;
    data[5] = 0xf;
    data[6] = 0;
    data[7] = 3;

    InitTextLayerDefault((u8 *)data_ov002_0206c460 + 0x48, 3, value, data);
    data_ov002_0206c460->flags10.initialized = 1;
}
