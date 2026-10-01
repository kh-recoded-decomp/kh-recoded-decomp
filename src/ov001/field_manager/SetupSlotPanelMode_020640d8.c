#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x27f1];
    u8 lowBits : 4;
    u8 slotsReady : 1;
} FieldState;

extern FieldState *data_ov001_020a0460;

extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern u32 func_0200d594(u32 value);
extern BOOL InitSlotLayout_0207d2c0(int first, int second);
extern BOOL InitSlotLayoutCompact_0207d320(u32 mode);
extern void func_ov001_020645dc(u32 flag);
extern void func_ov001_020645e8(u32 flag);
extern int func_ov001_0207d384(int value);

void SetupSlotPanelMode_020640d8(int mode, int enable) {
    FieldState *field = data_ov001_020a0460;

    switch (mode) {
    case 0:
        if (enable) {
            if (!field->slotsReady) {
                InitSlotLayout_0207d2c0(0x10, func_0200d594(ReadSessionPackedBits_02064574(0x3700, 0x10)));
                field->slotsReady = 1;
            }
            func_ov001_020645dc(0x3716);
        } else {
            func_ov001_020645e8(0x3716);
        }
        break;
    case 1:
        if (enable) {
            if (!field->slotsReady) {
                InitSlotLayoutCompact_0207d320(ReadSessionPackedBits_02064574(0x3700, 0x10));
                field->slotsReady = 1;
            }
            func_ov001_020645dc(0x3714);
        } else {
            func_ov001_020645e8(0x3714);
        }
        break;
    case 2:
        if (enable && !field->slotsReady) {
            field->slotsReady = 1;
        }
        break;
    }
    func_ov001_0207d384(enable);
}
