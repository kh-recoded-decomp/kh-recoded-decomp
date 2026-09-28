#include "nitro/types.h"

typedef struct Ov081State {
    u32 archive;
    u8 pad_04[0x6344];
    u8 *bitIndexTable;
} Ov081State;

extern void *func_0202c478(u32 fileId, u32 heapId);

void LoadBitIndexTable_020c5160(Ov081State *state)
{
    state->bitIndexTable = func_0202c478(((state->archive + 0x8000) & 0xfffffc) << 7 | 0x80000006, 0xe);
}
