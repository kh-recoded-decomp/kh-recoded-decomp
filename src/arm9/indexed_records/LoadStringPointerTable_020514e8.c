#include "nitro/types.h"

typedef struct StringTable {
    u8 header[0x28];
    u16 *strings[0x9a];
} StringTable;

typedef struct {
    u32 baseA;
    u32 baseB;
    u32 pad_08[4];
    StringTable *table;
    u8 *file;
} State;

extern State *data_020613d0;
extern u32 func_0202c478(u32 fileId, u32 param2);
extern u32 func_0202c48c(u32 fileId, u32 param2);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int alignment);
extern void func_01ff8830(void *dst, int value, int size);
extern void func_01ff8710(const void *src, void *dst, int size);
extern u16 *SkipWideString_020513a0(u16 *text);

void LoadStringPointerTable_020514e8(int useAlt)
{
    State *state = data_020613d0;
    StringTable *table;
    int i;

    if (useAlt != 0) {
        state->file = (u8 *)func_0202c48c(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000002, 0x11);
        state->table = NNSi_FndAllocFromDefaultHeapEx_0202a19c(sizeof(StringTable), -4);
    } else {
        state->file = (u8 *)func_0202c478(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000002, 0x11);
        state->table = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(StringTable));
    }
    table = state->table;
    func_01ff8830(table, 0, sizeof(StringTable));
    func_01ff8710(state->file, table, 0x28);
    table->strings[0] = (u16 *)(state->file + 0x28);
    /* Strings are packed back to back */
    for (i = 1; i < 0x9a; i++) {
        table->strings[i] = SkipWideString_020513a0(table->strings[i - 1]);
    }
}
