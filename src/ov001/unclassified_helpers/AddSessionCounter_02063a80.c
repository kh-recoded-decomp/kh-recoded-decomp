#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Session {
    u8 pad_0000[0x2938];
    s32 counters[29];
} Session;

extern Session *data_ov001_020a0460;
extern s32 data_ov001_0209d918[];
extern BOOL PXI_Init_020880d8(VecFx32 *out);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void func_ov001_02066514(u16 *amounts, void *position, int popupFlags);
extern void func_0202737c(int messageId, int category, int amount, int limit);
extern void func_ov001_020645e8(u32 eventId);
extern int func_ov001_020644b0(void);
extern u32 func_ov001_02064574(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

void AddSessionCounter_02063a80(int index, int amount) {
    int popupFlags;
    s32 *counters = data_ov001_020a0460->counters;
    int value;
    counters[index] += amount;
    if (amount > 0) {
        value = data_ov001_0209d918[index];
        if (value < counters[index]) {
            counters[index] = value;
        }
    } else if (counters[index] < 0) {
        counters[index] = 0;
    }
    switch (index) {
    case 1:
        if (amount < 0) {
            VecFx32 target;
            u16 amounts[6] = {0};
            popupFlags = 4;
            amounts[4] = -amount;
            if (PXI_Init_020880d8(&target)) {
                popupFlags = 5;
            }
            func_ov001_02066514(amounts, func_ov001_0206dc4c(0), popupFlags);
            return;
        }
        func_0202737c(0xb37, 0x11, amount, 99999);
        return;
    case 12:
        func_ov001_020645e8(0x35ca);
        return;
    case 28:
        if (func_ov001_020644b0() == 100) {
            value = func_ov001_02064574(0x3700, 7);
            value += amount;
            if (value >= 99) {
                value = 99;
            }
            WriteSessionPackedBits_0206459c(0x3700, 7, value);
        }
        func_0202737c(0xaf3, 0x11, amount, 99999);
        return;
    }
}
