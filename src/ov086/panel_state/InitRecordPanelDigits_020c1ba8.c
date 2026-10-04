#include "nitro/types.h"

typedef struct {
    u32 cellFileId;
    u32 unk04[3];
} ObjManagerConfig;

typedef struct {
    int x;
    int y;
} CellPosition;

typedef struct {
    int gaps[9];
} DigitGapTable;

typedef struct {
    u8 pad000[0x110];
    int digitCells[9];
} RecordPanel;

extern u8 *data_0205fe0c;
extern const ObjManagerConfig data_ov086_020c2128;
extern const DigitGapTable data_ov086_020c228c;
extern void *func_ov039_020bc1cc(void);
extern u32 BuildSlotImageParams_020bc220(int slot, u32 low);
extern int InitializeResourceContainer_020b8bd4(void *container, void *config);
extern void InitObjManagerAndMark_020b9060(void *container, ObjManagerConfig *config);
extern void PXI_Init_020b9078(void *container, u32 value);
extern void func_ov027_020b8f98(void *container, u32 fileId, int count);
extern void SetAllElementObjectModes_020b97fc(void *container, int mode);
extern void func_ov086_020c1470(void *container, int layer, CellPosition *position, u32 digit);
extern int func_0204f0b4(void *manager, u32 source, int enable);
extern void func_0204f13c(void *manager, int cell, CellPosition *position);
extern void func_0204f2e4(void *manager, int cell);
extern void func_0204f204(void *widget, int cell, u16 frame);
extern void func_0204f378(void *widget, int cell, BOOL visible);
extern void ResolveEntryStoreWord_020b9088(void *container, int elementId, void (*callback)(void));
extern void OnSliderTouched_020c2040(void);

void InitRecordPanelDigits_020c1ba8(RecordPanel *panel)
{
    void *container = func_ov039_020bc1cc();
    ObjManagerConfig config = data_ov086_020c2128;
    CellPosition position;
    DigitGapTable gapTable;
    int i;
    int x;
    u32 value;
    u32 digit;

    value = *(u32 *)(data_0205fe0c + 0x28d0);
    config.cellFileId = BuildSlotImageParams_020bc220(2, 0x15);
    InitializeResourceContainer_020b8bd4(container, NULL);
    InitObjManagerAndMark_020b9060(container, &config);
    PXI_Init_020b9078(container, BuildSlotImageParams_020bc220(3, 0));
    func_ov027_020b8f98(container, BuildSlotImageParams_020bc220(2, 0x14), 0x11);
    SetAllElementObjectModes_020b97fc(container, 1);
    x = 0x43;
    position.y = 0xa4000;
    do {
        position.x = x << 12;
        digit = value % 10;
        value /= 10;
        func_ov086_020c1470(container, 0, &position, digit);
        x -= 7;
    } while (value != 0);
    gapTable = data_ov086_020c228c;
    position.y = 0xb4000;
    x = 0x43;
    for (i = 0; i < 9; i++) {
        panel->digitCells[i] = func_0204f0b4(container, 1, 0);
        position.x = x << 12;
        func_0204f13c(container, panel->digitCells[i], &position);
        func_0204f2e4(container, panel->digitCells[i]);
        x -= gapTable.gaps[i];
    }
    func_0204f204(container, panel->digitCells[2], 10);
    func_0204f204(container, panel->digitCells[5], 10);
    func_0204f378(container, panel->digitCells[7], FALSE);
    func_0204f378(container, panel->digitCells[8], FALSE);
    ResolveEntryStoreWord_020b9088(container, 0x15, OnSliderTouched_020c2040);
}
