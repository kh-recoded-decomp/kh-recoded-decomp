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
    u8 index;
    u8 pad_26[0x30 - 0x26];
} CellSprite;

typedef struct GaugePanel {
    CellSprite cells[3];
    u8 blinkPanel[0x128];
    CellSize size;
    int timer;
    int fillLevel;
    fx32 fillScale;
} GaugePanel;

extern char data_ov059_020cff88[];
extern void CellPanel_Init_020cf230(void *panel);
extern void *RetainOrInitializeSharedRecord_0202c80c(const char *name, int kind);
extern void func_0202c690(int mode);
extern void *func_0202c940(void *info, void *textureHeader, int flag);
extern int func_0202d3c8(void *objectBase, int recordIndex);
extern int func_0202d3e0(void *objectBase, int recordIndex, int entryIndex);
extern void SetSlotKeyAndRebind_0206a94c(CellSprite *cell, int data, int arg);
extern int Slot_SetCellData_0206a93c(CellSprite *cell, int data, int stop, int index);
extern int ReleaseSharedRecordSlot_0202c8a8(void *slot);

void GaugePanel_Init_020cf8d8(GaugePanel *panel) {
    u32 i;
    void *objectBase;
    void *info;

    CellPanel_Init_020cf230(panel->blinkPanel);
    i = 0;
    panel->fillLevel = 0;
    panel->fillScale = 0x1000;
    info = RetainOrInitializeSharedRecord_0202c80c(data_ov059_020cff88, 0x11);
    func_0202c690(0);
    objectBase = func_0202c940(info, NULL, 1);
    func_0202c690(1);
    func_0202d3c8(objectBase, 7);
    for (; i < 2; i++) {
        CellSprite *cell = &panel->cells[i];
        SetSlotKeyAndRebind_0206a94c(cell, func_0202d3e0(objectBase, 7, i), 0);
        cell->width = 32;
        cell->height = 32;
        cell->flags |= 0xf0000;
        cell->alpha = 0x3f;
        panel->size.height = 0x5f800;
        panel->size.width = panel->size.height * 4 / 3;
        cell->size = panel->size;
    }
    Slot_SetCellData_0206a93c(&panel->cells[2], func_0202d3e0(objectBase, 7, 0), 0, 1);
    panel->cells[2].x /= 2;
    panel->cells[2].flags |= 0xf0000;
    panel->cells[2].alpha = 0x3f;
    ReleaseSharedRecordSlot_0202c8a8(info);
}
