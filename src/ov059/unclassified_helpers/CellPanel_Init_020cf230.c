#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CellSize {
    fx32 width;
    fx32 height;
} CellSize;

typedef struct CellSprite {
    s16 x;
    s16 y;
    u16 width;
    u16 height;
    u32 flags;
    u8 pad_0c[0x10 - 0xc];
    CellSize size;
    u8 pad_18[0x24 - 0x18];
    u8 alpha;
    u8 pad_25[0x30 - 0x25];
} CellSprite;

typedef struct CellPanel {
    CellSprite cells[2];
    u8 pad_060[0x121 - 0x60];
    u8 state;
    u8 pad_122[0x128 - 0x122];
} CellPanel;

extern char data_ov059_020cff74[];
extern void func_01ff86fc(u32 value, void *dst, u32 size);
extern void *RetainOrInitializeSharedRecord_0202c80c(const char *name, int kind);
extern void func_0202c690(int mode);
extern void *func_0202c940(void *info, void *textureHeader, int flag);
extern int func_0202d3c8(void *objectBase, int recordIndex);
extern int func_0202d3e0(void *objectBase, int recordIndex, int entryIndex);
extern int Slot_SetCellData_0206a93c(CellSprite *cell, int data, int stop, int index);
extern int ReleaseSharedRecordSlot_0202c8a8(void *slot);

void CellPanel_Init_020cf230(CellPanel *panel) {
    int i = 0;
    void *info;
    void *objectBase;
    CellSize size;

    func_01ff86fc(0, panel, sizeof(CellPanel));
    info = RetainOrInitializeSharedRecord_0202c80c(data_ov059_020cff74, 0x11);
    func_0202c690(0);
    objectBase = func_0202c940(info, NULL, 1);
    func_0202c690(1);
    func_0202d3c8(objectBase, 7);
    for (; i < 2; i++) {
        Slot_SetCellData_0206a93c(&panel->cells[i], func_0202d3e0(objectBase, 7, 0), 0, i);
    }
    panel->cells[0].width = 16;
    panel->cells[0].height = 16;
    panel->cells[0].flags |= 0xf0000;
    panel->cells[0].alpha = 0x3f;
    panel->cells[1].x /= 2;
    panel->cells[1].flags |= 0xf0000;
    ReleaseSharedRecordSlot_0202c8a8(info);
    size.height = 0x5f800;
    size.width = size.height * 4 / 3;
    panel->cells[0].size = size;
    panel->state = 5;
}
